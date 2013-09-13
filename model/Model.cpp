/* 
 * File:   Model.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 3:10 PM
 */

#include <boost/assert.hpp>
#include <algorithm>
#include <queue>
#include <fstream>
#include "Model.h"
#include "spnet/Spn.h"

namespace model
{

Model::Model()
{
}

Model::Model(const std::string& modelName
    , std::vector<Node*> &nodes
    , std::vector<Edge*> &edges)
: m_nodes(nodes)
, m_edges(edges)
{
}

Model::~Model()
{
    m_nodeList.clear();
    deleteList(m_nodes);
    m_nodes.clear();
    deleteList(m_edges);
    m_edges.clear();
}

/*****************************************************************************/

std::string Model::GetName()
{
    return m_modelData.name();
}

/*****************************************************************************/
bool Model::Validate()
{
    m_nodeList.clear();
    std::vector<bool> removedEdges(m_edges.size());
    std::fill(removedEdges.begin(), removedEdges.end(), false);
    
    // get all nodes without incomining edges
    std::deque<Node*> S;
    for (std::vector<Node*>::iterator it = m_nodes.begin(); 
            it != m_nodes.end(); ++it)
    {
        if ((*it)->GetIncomingEdgesCount() == 0)
            S.push_back(*it);
    }
    
    while(!S.empty())
    {
        Node* n = S.front();
        S.pop_front();
        m_nodeList.push_back(n);
        std::vector<Edge*>& neighbors = n->GetOutgoingEdges();
        for (std::vector<Edge*>::iterator itEdge = neighbors.begin();
                itEdge != neighbors.end(); ++itEdge)
        {
            size_t idx = std::distance(m_edges.begin(), 
                    std::find(m_edges.begin(), m_edges.end(), (*itEdge)));
            BOOST_ASSERT(idx < m_edges.size());
            removedEdges[idx] = true;
            
            // check neighbors[i].node2 has any edge
            bool bAllRemoved = true;
            std::vector<Edge*>& incomingOfNode2 = (*itEdge)->GetNode2()->GetIncomingEdges();
            for (std::vector<Edge*>::iterator itEdge2 = incomingOfNode2.begin();
                    itEdge2 != incomingOfNode2.end(); ++itEdge2)
            {
                size_t idx2 = std::distance(m_edges.begin(), 
                    std::find(m_edges.begin(), m_edges.end(), *itEdge2));
                BOOST_ASSERT(idx2 < m_edges.size());
                if (!removedEdges[idx2])
                {
                    bAllRemoved = false;
                    break;
                }
            }
            if (bAllRemoved)
            {
                S.push_back((*itEdge)->GetNode2());
            }
        }
    }
    
    if (removedEdges.end() != std::find(removedEdges.begin(), removedEdges.end(), false))
    {
        m_nodeList.clear();
        return false;
    }
    return true;
}

void Model::PrintBackpropOrder(std::ostream& s)
{
    if (m_nodeList.empty())
        return;
    
    s << "Backprop order: ";
    for (std::vector<Node*>::iterator it = m_nodeList.begin();
            it != m_nodeList.end(); ++it)
    {
        s << (*it)->GetName() << " ";
    }
    s << std::endl;
}

void Model::ToModelData(ModelData& modelData)
{
    modelData.CopyFrom(m_modelData);
    
    std::vector<Node*>::iterator itNode;
    std::vector<Edge*>::iterator itEdge;
    
    // nodes
    modelData.clear_nodes();
    for (itNode = m_nodes.begin(); itNode != m_nodes.end(); ++itNode)
    {
        NodeData *nodeData = modelData.add_nodes();
        (*itNode)->ToNodeData(*nodeData);
    }
        
    // edges
    modelData.clear_edges();
    for (itEdge = m_edges.begin(); itEdge != m_edges.end(); ++itEdge)
    {
        EdgeData *edgeData = modelData.add_edges();
        (*itEdge)->ToEdgeData(*edgeData);
    }
}

Model* Model::FromModelData(const ModelData& modelData)
{
    switch(modelData.model_type())
    {
        case ModelData::SPN:
            return Spn::FromProto(modelData);
        default:
            return NULL;
    }
}

/***************************************************************************/

template <typename T>
void Model::deleteList(const std::vector<T*>& vList)
{
    for (int i = vList.size() - 1; i >= 0; --i)
    {
        delete (vList[i]);
    }
}

}