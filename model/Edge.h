/* 
 * File:   Edge.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 3:17 PM
 */

#ifndef EDGE_H
#define	EDGE_H

#include <pimatrix.h>
#include <Node.h>

namespace model
{

class Node;

class Edge
{

private:
    math::pimatrix m_weight;
    Node *m_node1, *m_node2;
    bool m_bDirected;
    
public:
    Edge(Node *node1, Node* node2, bool directed);
    Edge(const Edge& orig);
    virtual ~Edge();
    
    Node* GetNode1()
    {
        return m_node1;
    }
    
    Node* GetNode2()
    {
        return m_node2;
    }
    
private:

};

}

#endif	/* EDGE_H */

