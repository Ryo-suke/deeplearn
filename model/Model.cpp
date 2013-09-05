/* 
 * File:   Model.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 3:10 PM
 */

#include "Model.h"

#include <algorithm>
#include <boost/assert.hpp>

namespace model
{

Model::Model()
{
}

Model::Model(std::vector<Node*> &nodes, std::vector<Edge*> &edges)
: m_nodes(nodes)
, m_edges(edges)
{
}

Model::Model(const Model& orig)
{
}

Model::~Model()
{
}

bool Model::SortNodes()
{
    int i;
    
    m_nodeList.clear();
    std::vector<bool> removedEdges(m_edges.size());
    std::fill(removedEdges.begin(), removedEdges.end(), false);
    
    // get all nodes without incomining edges
    std::vector<Node*> S;
    for (i = m_nodes.size() - 1; i >= 0 ; --i)
    {
        if (m_nodes[i].GetIncomingEdgesCount() == 0)
            S.push_back(m_nodes[i]);
    }
    
    while(!S.empty())
    {
        Node* n = S.pop_back();
        m_nodeList.push_back(n);
        std::vector<Edge*>& neighbors = n->GetOutgoingEdges();
        for (i = neighbors.size() - 1; i >= 0; --i)
        {
            int idx = std::distance(m_edges.begin(), 
                    std::find(m_edges.begin(), m_edges.end(), neighbors[i]));
            BOOST_ASSERT(idx < m_edges.size());
            removedEdges[idx] = true;
            
            // check neighbors[i].node2 has any edge
        }
    }
}

}