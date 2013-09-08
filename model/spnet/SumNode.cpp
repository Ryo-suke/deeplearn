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

SumNode::SumNode(NodeData& nodeData)
: Node(nodeData)
{
}

SumNode::~SumNode()
{
}

void SumNode::Forward()
{
    // weighted sum
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
}

}