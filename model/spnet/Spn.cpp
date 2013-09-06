/* 
 * File:   spn.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 5:34 PM
 */

#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>

#include <spnet/Spn.h>
#include <pimatrix.h>
#include "InputNode.h"
#include "MaxNode.h"
#include "ProductNode.h"
#include "SumNode.h"

namespace model
{

Spn::Spn()
{   }

Spn::~Spn()
{
    m_inputNodes.clear();
    m_hiddenNodes.clear();
    m_queryNodes.clear();
}

/**************************************************************************/

void Spn::Train(data::DataHandler* dataHandler, Operation& trainOp)
{
    BOOST_ASSERT_MSG(!m_nodeList.empty(),
            "No backprop order. Please run SortNodes() first.");
    // check valid data handler and network architecture
    
    Operation_StopCondition stopCond = trainOp.stop_condition();
    if (stopCond.all_processed())
    {
        stopCond.set_steps(dataHandler->GetNumBatches());
    }
    dataHandler->SetBatchSize(trainOp.batch_size());
    
    math::pimatrix* currentBatch;
    int iTrainStep = 0;
    
    while (stopCondition(stopCond, iTrainStep))
    {
        dataHandler->EndLoadNextBatch();
        currentBatch = dataHandler->GetCurrentBatch();
        TrainOneBatch(trainOp, currentBatch);
    }
    Prune();
}

/**************************************************************************/

void Spn::TrainOneBatch(Operation& trainOp
                    , math::pimatrix* batch)
{
    std::vector<Node*>::iterator it;
    
    for(it = m_inputNodes.begin(); it != m_inputNodes.end(); ++it)
    {
        (*it)->SetValue(batch);
    }
    
    // set 1 for H
    
    // set query (target)
    for(it = m_queryNodes.begin(); it != m_queryNodes.end(); ++it)
    {
        (*it)->SetValue(batch);
    }
    
    for (it = m_nodeList.begin(); it != m_nodeList.end(); ++it)
    {
        (*it)->Forward();
    }
    
    // get value of root
    
}

void Prune()
{
    
}

bool Spn::stopCondition(const Operation_StopCondition& cond, int iStep)
{
    return iStep < cond.steps();
}

/**************************************************************************/

Spn* Spn::FromProto(const ModelData& modelData)
{
    const model::SpnData &spnData = modelData.spn_data();
    
    math::pimatrix nodeList(spnData.node_list());
    math::pimatrix adjMatrix(spnData.adjacency_matrix());
    math::pimatrix inputIndices(spnData.input_indices());
    
    if (nodeList.size1() != 1 
            || nodeList.size2() < 1
            || adjMatrix.size1() != adjMatrix.size2()
            || adjMatrix.size1() != nodeList.size2())
        // invalid data
        return NULL;
    
    std::vector<Node*> nodes, inputNodes, hiddenNodes, queryNodes;
    std::vector<Edge*> edges;
    Node* tmpNode;
    NodeData nodeData = NodeData::default_instance();
    size_t i;
    
    nodeData.set_dimension(1);         // every node in SPN has dimension of 1
    
    for (i = 0; i < nodeList.size2(); ++i)
    {
        nodeData.set_name(boost::lexical_cast<std::string>(i));
        
        switch((unsigned int)nodeList(0, i))
        {
            case NodeData::INPUT:
                nodeData.set_type(NodeData::INPUT);
                nodeData.set_input_start_index(inputIndices(0, i));
                tmpNode = new InputNode(nodeData);
                inputNodes.push_back(tmpNode);
                break;
            case NodeData::HIDDEN:
                nodeData.set_type(NodeData::HIDDEN);
                tmpNode = new InputNode(nodeData);
                hiddenNodes.push_back(tmpNode);
                break;
            case NodeData::QUERY:
                nodeData.set_type(NodeData::QUERY);
                nodeData.set_input_start_index(inputIndices(0, i));
                tmpNode = new InputNode(nodeData);
                queryNodes.push_back(tmpNode);
                break;
            case NodeData::SUM:
                nodeData.set_type(NodeData::SUM);
                tmpNode = new SumNode(nodeData);
                break;
            case NodeData::PRODUCT:
                nodeData.set_type(NodeData::PRODUCT);
                tmpNode = new ProductNode(nodeData);
                break;
            case NodeData::MAX:
                nodeData.set_type(NodeData::MAX);
                tmpNode = new MaxNode(nodeData);
                break;
            default:
                Model::deleteList(nodes);
                nodes.clear();
                return NULL;
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
                return NULL;
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
    
    Spn* spn = new Spn();
    spn->m_modelName = modelData.name();
    spn->m_edges.assign(edges.begin(), edges.end());
    spn->m_nodes.assign(nodes.begin(), nodes.end());
    spn->m_inputNodes.assign(inputNodes.begin(), inputNodes.end());
    spn->m_hiddenNodes.assign(hiddenNodes.begin(), hiddenNodes.end());
    spn->m_queryNodes.assign(queryNodes.begin(), queryNodes.end());
    

    return spn;
}


}