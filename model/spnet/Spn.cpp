/* 
 * File:   spn.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 5:34 PM
 */

#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <spnet/Spn.h>
#include <pimatrix.h>
#include "InputNode.h"
#include "MaxNode.h"
#include "ProductNode.h"
#include "SumNode.h"
#include "Util.h"

namespace model
{

Spn::Spn()
: m_root(NULL)
{   }

Spn::~Spn()
{
    m_inputNodes.clear();
    m_hiddenNodes.clear();
    m_queryNodes.clear();
}

/**************************************************************************/

math::pimatrix Spn::Forward(math::pimatrix* batch)
{
    std::vector<Node*>::iterator it;
    
    // set data
    if (batch)
    {
        for(it = m_inputNodes.begin(); it != m_inputNodes.end(); ++it)
        {
            (*it)->SetValue(*batch);
        }

        // set 1 for H
        for(it = m_hiddenNodes.begin(); it != m_hiddenNodes.end(); ++it)
        {
            (*it)->SetValue(1.0f, batch->size1());
        }

        // set query (target)
        for(it = m_queryNodes.begin(); it != m_queryNodes.end(); ++it)
        {
            (*it)->SetValue(*batch);
        }
    }
    
    for (it = m_nodeList.begin(); it != m_nodeList.end(); ++it)
    {
        (*it)->Forward();
    }    
    // get value of root
    return m_root->GetActivations();
}

void Spn::Backward()
{
    std::vector<Node*>::reverse_iterator it;
    
    for (it = m_nodeList.rbegin(); it != m_nodeList.rend(); ++it)
    {
        (*it)->Backward();
    } 
}

void Spn::Train(Operation& trainOp, Operation* evalOp /*= NULL*/)
{
    BOOST_ASSERT_MSG(!m_nodeList.empty() && m_root,
            "No backprop order. Please run Validate() first.");
    
    // load data handler
    data::DataHandler* dataHandler = util::Util::LoadDataHandler(
            trainOp.data_proto(), trainOp.randomize()
            , trainOp.random_seed(), trainOp.verbose());
    if (!dataHandler)
        return;
    
    data::Dataset* trainSet = dataHandler->GetDataset(model::DatasetInfo_Data::TRAIN_SET);
    
    // set batch size and training stop condition
    trainSet->SetBatchSize(trainOp.batch_size());
	Operation_StopCondition stopCond = trainOp.stop_condition();
	if (stopCond.all_processed())
	{
		stopCond.set_steps(trainSet->GetNumBatches());
    }
    
    
    math::pimatrix* currentBatch;
    int iTrainStep = 0;
    boost::filesystem::path cpDir(trainOp.checkpoint_directory());
    boost::format fmtCpFile("%1%_%2%_%3%.bin");
    
    for (; stopCondition(stopCond, iTrainStep); ++iTrainStep)
    {
        // load data, this is for asynchronous data loading
        trainSet->EndLoadNextBatch();
        currentBatch = trainSet->GetCurrentBatch();
        trainSet->BeginLoadNextBatch();
        
        // train current batch
        TrainOneBatch(trainOp, currentBatch, iTrainStep);
        
        if (evalCondition(trainOp.eval_after(), iTrainStep) && evalOp)
        {
            // evaluation
        }
        if (checkpointCondition(trainOp.checkpoint_after(), iTrainStep))
        {
            fmtCpFile % GetName() % trainOp.name() % iTrainStep;
            boost::filesystem::path cpFile(fmtCpFile.str());
            boost::filesystem::path cpFullPath = cpDir / cpFile;
            ToFile(cpFullPath.generic_string());           
        }
    }
    Prune();
}

bool Spn::Validate()
{
	bool bRet = Model::Validate();
	if (!bRet)
		return false;

	// find root
    m_root = NULL;
    std::vector<Node*>::iterator it = m_nodeList.begin();
    for(; it != m_nodeList.end(); it++)
    {
        if((*it)->GetOutgoingEdgesCount() == 0)
        {
            if (m_root)
                return false;
            else
                m_root = (*it);
        }
    }
    
    // in SPN, the root must be the last one..
    Node* lastNode = (*m_nodeList.rbegin());
    return m_root != NULL && m_root == lastNode;
}

/**************************************************************************/

void Spn::TrainOneBatch(Operation& trainOp
                    , math::pimatrix* batch, int iTrainStep)
{
    std::vector<Node*>::iterator it;
    size_t nSamples = batch->size1();
    
    // quite tricky here: we construct 2 set of samples,
    // the first set is for the positive phase
    // and the second for the negative phase
    math::pimatrix twoBatch(nSamples*2, batch->size2());
    
    twoBatch.copyRows(*batch, 0, nSamples, 0);
    twoBatch.copyRows(*batch, 0, nSamples, nSamples);
    
    // set query variables of the second half to 1
    for(it = m_queryNodes.begin(); it != m_queryNodes.end(); ++it)
    {
         twoBatch.setValue(1.0f, nSamples, nSamples
                 , (*it)->GetInputStartIndex(), (*it)->GetDimension());
    }
    
    // get the error (actually the probability at the root)
    m_error = Forward(&twoBatch);
    
    // then we negate the error of half of the "batch"
    BOOST_ASSERT(m_error.size1() == 2*nSamples && m_error.size2() == 1);
    m_error.element_inverse();
    m_error.element_negate(nSamples, nSamples, 0, 1);
    
    for(it = m_nodeList.begin(); it != m_nodeList.end(); ++it)
    {
        (*it)->InitializeDerivative();
    }
    m_root->AccumDerivatives(m_error);
    
    // and do backward.
    Backward();
    
    // lastly: update parameters
    std::vector<Edge*>::iterator itEdge;
    for(itEdge = m_edges.begin(); itEdge != m_edges.end(); ++itEdge)
    {
        (*itEdge)->UpdateParams(iTrainStep);
    }
    
    // update parameters for nodes. Normally this is not 
    // neccessary for SPN where nodes do not have biases.
    for(it = m_nodes.begin(); it != m_nodes.end(); ++it)
    {
        (*it)->UpdateParams(iTrainStep);
    }
}

void Spn::Prune()
{
    
}

bool Spn::stopCondition(const Operation_StopCondition& cond, int iStep)
{
    return iStep < cond.steps();
}

bool Spn::evalCondition(int eval_after, int iStep)
{
    return ((iStep % eval_after) == 0);
}

bool Spn::checkpointCondition(int checkpoint_after, int iStep)
{
    return ((iStep % checkpoint_after) == 0);
}

/**************************************************************************/

template <NodeData_NodeType t>
bool filterNode(Node *n)
{
    return n->GetNodeType() == t;
}

Spn* Spn::FromProto(const ModelData& modelData)
{
    BOOST_ASSERT_MSG(modelData.model_type() == model::ModelData::SPN,
            "modelData does not represent an SPN.");
    
    std::vector<Node*> nodes, inputNodes, hiddenNodes, queryNodes;
    std::vector<Edge*> edges;
    
    if (modelData.has_spn_data())
    {
        if(!Spn::LoadSpnInits(modelData.spn_data(), nodes, edges))
            return NULL;
    }
    
    if (modelData.nodes_size() > 0 || modelData.edges_size() > 0)
    {
        Spn::LoadSpnStructure(modelData, nodes, edges);
    }
    
    if (nodes.size() == 0 || edges.size() == 0)
    {
        return NULL;
    }
    
    std::vector<Node*>::iterator it = nodes.begin();
    for (; it != nodes.end(); ++it)
    {
        switch((*it)->GetNodeType())
        {
            case NodeData::INPUT:
                inputNodes.push_back(*it);
                break;
            case NodeData::HIDDEN:
                hiddenNodes.push_back(*it);
                break;
            case NodeData::QUERY:
                queryNodes.push_back(*it);
                break;
        }
        
        // merge hyper-parameters
        (*it)->MergeHyperparams(modelData.hyper_params());
    }
    
    if (modelData.has_hyper_params())
    {
        for (std::vector<Edge*>::iterator itEdge = edges.begin();
                itEdge != edges.end(); ++itEdge)
        {
            (*itEdge)->MergeHyperparams(modelData.hyper_params());
        }
    }
    
    Spn* spn = new Spn();
    spn->m_modelData.MergeFrom(modelData);
    spn->m_edges.assign(edges.begin(), edges.end());
    spn->m_nodes.assign(nodes.begin(), nodes.end());
    spn->m_inputNodes.assign(inputNodes.begin(), inputNodes.end());
    spn->m_hiddenNodes.assign(hiddenNodes.begin(), hiddenNodes.end());
    spn->m_queryNodes.assign(queryNodes.begin(), queryNodes.end());
    
    return spn;
}


bool Spn::LoadSpnInits(const SpnData& spnData
                , std::vector<Node*>& nodes, std::vector<Edge*>& edges)
{
    math::pimatrix nodeList(spnData.node_list());
    math::pimatrix adjMatrix(spnData.adjacency_matrix());
    math::pimatrix inputIndices(spnData.input_indices());
    
    if (nodeList.size1() != 1 
            || nodeList.size2() < 1
            || adjMatrix.size1() != adjMatrix.size2()
            || adjMatrix.size1() != nodeList.size2())
    {
        std::cout << "ERR\tSpnData in the proto file is invalid" << std::endl;
        return false;
    }
    
    Node* tmpNode;
    NodeData nodeData;
    size_t i;
    
    // every node in SPN has dimension of 1
    nodeData.set_dimension(1);
    
    for (i = 0; i < nodeList.size2(); ++i)
    {
        // name
        nodeData.set_name(boost::lexical_cast<std::string>(i));

        // type
        if (!NodeData_NodeType_IsValid((int)nodeList(0, i)))
        {
            Model::deleteList(nodes);
            nodes.clear();
            std::cout << "ERR\tInvalid node type: " << nodeList(0, i)
                        << " at location " << i << " in node_list." << std::endl;
            return false;
        }
        NodeData_NodeType nodeType = (NodeData_NodeType)(int)nodeList(0, i);
        nodeData.set_type(nodeType);
        
        // input start index
        if (nodeType == NodeData::INPUT || nodeType == NodeData::QUERY)
        {
            int inputIdx = (int)inputIndices(0, i);
            if (inputIdx < 0)
            {
                Model::deleteList(nodes);
                nodes.clear();
                std::cout << "ERR\tInvalid input index: " << inputIdx
                          << " at location " << i << " in input_indices." 
                          << std::endl;
                return false;
            }
            nodeData.set_input_start_index(inputIdx);
        }
        
        // create the node
        tmpNode = CreateNewNode(nodeData);
        if (!tmpNode)
        {
            Model::deleteList(nodes);
            nodes.clear();
            return false;
        }
        nodes.push_back(tmpNode);
    }
    
    // process the adjacency matrix
    for (i = 0; i < adjMatrix.size1(); ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            if(adjMatrix(i, j) != 0 && adjMatrix(j, i) != 0)
            {
                // should never happen with SPN because it is a directed model
                Model::deleteList(nodes);
                nodes.clear();
                Model::deleteList(edges);
                edges.clear();
                std::cout << "ERR\tThe adjacency matrix of SPN must be directed. " 
                        << "Check location (" << i << ", " << j
                        << ") in the adjacency matrix" << std::endl;
                return false;
            }
            else if (adjMatrix(i, j) != 0)
            {
                edges.push_back(new Edge(nodes.at(i), 
                        nodes.at(j), true));
            }
            else if (adjMatrix(j, i) != 0)
            {
                edges.push_back(new Edge(nodes.at(j), 
                        nodes.at(i), true));
            }
        }
    }
    return true;
}

bool findNodeByName(const std::string& sNodeName, Node* n)
{
    return sNodeName.compare(n->GetName()) == 0;
}

bool Spn::LoadSpnStructure(const ModelData& modelData
                , std::vector<Node*>& nodes, std::vector<Edge*>& edges)
{
    bool bNewModel = nodes.size() == 0 && edges.size() == 0;
    Node* newNode;
    std::vector<Node*>::iterator itFind;
    int i;
    
    // nodes
    for (i = modelData.nodes_size() - 1; i >= 0; --i)
    {
        const NodeData& nodeData = modelData.nodes(i);
        
        if (bNewModel)
        {
            newNode = Spn::CreateNewNode(nodeData);
            if (newNode)
            {
                nodes.push_back(newNode);
            }
            else
            {    std::cout << "Invalid node data with node name = " 
                          << nodeData.name()
                          << ". We ignore it and continue" << std::endl;
            }
        }
        else
        {
            itFind = std::find_if(nodes.begin(), nodes.end()
                    , boost::bind(findNodeByName, nodeData.name(), _1));
            if (itFind == nodes.end())
            {
                std::cout << "Ignore initialization of node: " 
                          << nodeData.name() << std::endl;
            }
            else
            {
                newNode = (*itFind);
                newNode->MergeNodeData(nodeData);
            }
        }
    }
    
    // edges
    Node *node1, *node2;
    Edge *newEdge;
    
    for (i = modelData.edges_size() - 1; i >= 0; --i)
    {
        const EdgeData& edgeData = modelData.edges(i);
        
        itFind = std::find_if(nodes.begin(), nodes.end()
                    , boost::bind(findNodeByName, edgeData.node1(), _1));
        if (itFind == nodes.end())
        {
            std::cout << "Couldn't find node: " << edgeData.node1()
                      << " so we ignore the edge " << edgeData.node1()
                      << " - " << edgeData.node2() << std::endl;
            continue;
        }
        node1 = (*itFind);
        
        itFind = std::find_if(nodes.begin(), nodes.end()
                    , boost::bind(findNodeByName, edgeData.node2(), _1));
        if (itFind == nodes.end())
        {
            std::cout << "Couldn't find node: " << edgeData.node2()
                      << " so we ignore the edge " << edgeData.node1()
                      << " - " << edgeData.node2() << std::endl;
            continue;
        }
        node2 = (*itFind);
        
        newEdge = new Edge(node1, node2, edgeData.directed());
        newEdge->MergeEdgeData(edgeData);
        edges.push_back(newEdge);
    }
    return true;
}

Node* Spn::CreateNewNode(const NodeData& nodeData)
{
    Node *tmpNode = NULL;
    
    switch(nodeData.type())
    {
        case NodeData::INPUT:
        case NodeData::HIDDEN:
        case NodeData::QUERY:
            tmpNode = new InputNode(nodeData);
            break;
        case NodeData::SUM:
            tmpNode = new SumNode(nodeData);
            break;
        case NodeData::PRODUCT:
            tmpNode = new ProductNode(nodeData);
            break;
        case NodeData::MAX:
            tmpNode = new MaxNode(nodeData);
            break;
        default:
            std::cout << "ERR\tNode type is not valid for SPN: " 
                    << nodeData.type() << std::endl;
    }
    return tmpNode;
}

}