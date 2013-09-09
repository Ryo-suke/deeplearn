/* 
 * File:   ProductNode.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 5, 2013, 12:03 PM
 */

#include "ProductNode.h"

namespace model
{

ProductNode::ProductNode(NodeData& nodeData)
: Node(nodeData)
{
}


ProductNode::~ProductNode()
{
}

void ProductNode::Forward()
{
    // weights of the edges are ignored
    std::vector<Edge*>::iterator it = m_incomingEdges.begin();
    int i = 0;
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

}