/* 
 * File:   SumNode.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 5, 2013, 12:03 PM
 */

#include <boost/assert.hpp>
#include "SumNode.h"

namespace model
{

SumNode::SumNode(const NodeData& nodeData)
: Node(nodeData)
{
}

SumNode::~SumNode()
{
}

void SumNode::Forward()
{
    // weighted sum
    std::vector<Edge*>::iterator it;
    int i = 0;
    for (it = m_incomingEdges.begin(); it != m_incomingEdges.end(); ++it)
    {
        BOOST_ASSERT((*it)->GetNode2() == this);
        
        if (i == 0)
            m_activations = (*it)->Forward();
        else
            m_activations += (*it)->Forward();
        i++;
    }
}

void SumNode::Backward()
{
    std::vector<Edge*>::iterator it;
    
    for (it = m_incomingEdges.begin(); it != m_incomingEdges.end(); ++it)
    {
        (*it)->Backward(m_derivatives);
    }
}

void SumNode::NormalizeIncomingEdges()
{
    std::vector<Edge*>::iterator it;
    int i = 0;
    math::pimatrix weightSum;
    
    // sum
    for (it = m_incomingEdges.begin(); it != m_incomingEdges.end(); ++it)
    {
        BOOST_ASSERT((*it)->GetNode2() == this);
        if (i == 0)
            weightSum = (*it)->GetWeight();
        else
            weightSum += (*it)->GetWeight();
        i++;
    }
    
    // normalize
    for (it = m_incomingEdges.begin(); it != m_incomingEdges.end(); ++it)
    {
        (*it)->NormalizeWeights(weightSum);
    }
    
}

}