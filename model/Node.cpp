/* 
 * File:   Node.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 2:50 PM
 */

#include "Node.h"
#include "InputNode.h"

namespace model
{

Node::Node(NodeData& nodeData)
{
    m_nodeData = nodeData;      // deep copy
}

Node::Node(const Node& orig)
{
}

Node::~Node()
{
    m_incomingEdges.clear();
    m_outgoingEdges.clear();
}



}