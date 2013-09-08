/* 
 * File:   Edge.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 3:17 PM
 */

#include "Edge.h"

namespace model
{

Edge::Edge(Node *node1, Node* node2, bool directed)
{
    m_node1 = node1;
    m_node2 = node2;
    m_bDirected = directed;
    
    m_weight.resize(m_node1->GetDimension(), m_node2->GetDimension(), false);
    
    m_node1->AddOutgoingEdge(this);
    m_node2->AddIncomingEdge(this);
    if (!m_bDirected)
    {
        m_node1->AddIncomingEdge(this);
        m_node2->AddOutgoingEdge(this);
    }
}

Edge::~Edge()
{
    m_node1 = m_node2 = NULL;
}

math::pimatrix Edge::Forward()
{
    BOOST_ASSERT(m_node1);
    math::pimatrix m = m_node1->GetActivations();
    m.mult(m_weight);
    return m;
}
    
}
