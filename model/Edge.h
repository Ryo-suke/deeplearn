/* 
 * File:   Edge.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 3:17 PM
 */

#ifndef EDGE_H
#define	EDGE_H

#include <boost/noncopyable.hpp>
#include <pimatrix.h>
#include <Node.h>

namespace model
{

class Node;

class Edge : boost::noncopyable
{

private:
    math::pimatrix m_weight;
    Node *m_node1, *m_node2;
    bool m_bDirected;
    
public:
    Edge(Node *node1, Node* node2, bool directed);
    virtual ~Edge();
    
    Node* GetNode1()
    {
        return m_node1;
    }
    
    Node* GetNode2()
    {
        return m_node2;
    }

    math::pimatrix& GetWeights()
    {
        return m_weight;
    }

    virtual math::pimatrix Forward();
    
private:

};

}

#endif	/* EDGE_H */

