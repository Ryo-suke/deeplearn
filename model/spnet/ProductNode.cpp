/* 
 * File:   ProductNode.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 5, 2013, 12:03 PM
 */

#include "ProductNode.h"

namespace model
{

ProductNode::ProductNode(const NodeData& nodeData)
: Node(nodeData)
{
}


ProductNode::~ProductNode()
{
}

void ProductNode::Forward()
{
    // weights of the edges are ignored in product node
    
    int i = 0;
    std::vector<Edge*>::iterator it = m_incomingEdges.begin();
    for (; it != m_incomingEdges.end(); ++it)
    {
        Node* incomingNeighbor = (*it)->GetNode1();

        BOOST_ASSERT((*it)->GetNode2() == this);
        BOOST_ASSERT_MSG(incomingNeighbor->GetDimension() == GetDimension()
            , "Invalid dimension");

        if (i == 0)
            m_activations = incomingNeighbor->GetActivations();
        else
            m_activations.dot(incomingNeighbor->GetActivations());
        i++;
    }
}

void ProductNode::Backward()
{
    std::vector<Edge*>::iterator it = m_incomingEdges.begin();
    math::pimatrix mProdActs = m_activations;
    mProdActs.element_mult(m_derivatives);
    
    for (; it != m_incomingEdges.end(); ++it)
    {
        Node* incomingNeighbor = (*it)->GetNode1();
        BOOST_ASSERT((*it)->GetNode2() == this);
        
        math::pimatrix tmp = mProdActs;
        tmp.element_div(incomingNeighbor->GetActivations());
        incomingNeighbor->AccumDerivatives(tmp);
    }
}

void ProductNode::NormalizeIncomingEdges()
{
    // doing nothing
}
}