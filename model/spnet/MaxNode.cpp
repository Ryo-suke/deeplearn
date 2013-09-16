/* 
 * File:   MaxNode.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 5, 2013, 12:03 PM
 */

#include "MaxNode.h"

namespace model
{

MaxNode::MaxNode(const NodeData& nodeData)
: Node(nodeData)
{
}

MaxNode::~MaxNode()
{
}

void MaxNode::Forward()
{
    /*
    std::vector<Edge*>::iterator it = m_incomingEdges.begin();
    int i = 0;
    for (; it != m_incomingEdges.end(); ++it)
    {
        BOOST_ASSERT((*it)->GetNode2() == this);
        
        if (i == 0)
            m_activations = (*it)->Forward();
        else
            m_activations += (*it)->Forward();
        i++;
    }
    */
}

void MaxNode::Backward()
{
    /*
    std::vector<Edge*>::iterator it = m_incomingEdges.begin();
    math::pimatrix mProdActs = m_activations;
    mProdActs.element_mult(m_derivatives);
    
    for (; it != m_incomingEdges.end(); ++it)
    {
        (*it)->Backward(m_derivatives);
    }
    */
}

void MaxNode::NormalizeIncomingEdges()
{
    // doing nothing
}

}