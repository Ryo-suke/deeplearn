/* 
 * File:   spn.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 5:34 PM
 */

#include <boost/lexical_cast.hpp>

#include <spnet/Spn.h>
#include <pimatrix.h>
#include "InputNode.h"
#include "MaxNode.h"
#include "ProductNode.h"
#include "SumNode.h"

namespace model
{

Spn::Spn(std::vector<Node*>& nodes
            , std::vector<Edge*>& edges
            , std::vector<Node*>& inputNodes
            , std::vector<Node*>& hiddenNodes
            , std::vector<Node*>& queryNodes)
: Model(nodes, edges)
, m_inputNodes(inputNodes)
, m_hiddenNodes(hiddenNodes)
, m_queryNodes(queryNodes)
{   }

Spn::Spn(const Spn& orig)
{
    
}

Spn::~Spn()
{
    
}

/**************************************************************************/

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
    int i;
    
    nodeData.set_dimension(1);         // every node in SPN has dimension of 1
    
    for (i = 0; i < nodeList.size2(); ++i)
    {
        nodeData.set_name(boost::lexical_cast<std::string>(i));
        
        switch((int)nodeList(0, i))
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
                tmpNode = new SumNode();
                break;
            case NodeData::PRODUCT:
                nodeData.set_type(NodeData::PRODUCT);
                tmpNode = new ProductNode();
                break;
            case NodeData::MAX:
                nodeData.set_type(NodeData::MAX);
                tmpNode = new MaxNode();
                break;
            default:
                Spn::deleteList(nodes);
                nodes.clear();
                return NULL;
        }
        nodes.push_back(tmpNode);
    }
    
    // process the adjacency matrix
    for (i = adjMatrix.size1() - 1; i >= 0; --i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (adjMatrix(i, j) != 0)
            {
                edges.push_back(new Edge(nodes[i], nodes[j], true));
            }
        }
    }
    return new Spn(nodes, edges, inputNodes, hiddenNodes, queryNodes);
}

template <typename T>
void Spn::deleteList(const std::vector<T*>& vList)
{
    for (int i = vList.size() - 1; i >= 0; --i)
    {
        delete (vList[i]);
    }
}

}