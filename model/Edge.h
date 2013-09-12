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
    /*
     * node1_size x node2_size
     */
    math::pimatrix m_weight;
    /*
     * node1_size x node2_size
     */
    math::pimatrix m_derivatives, m_oldDerivatives;
    
    Node *m_node1, *m_node2;

    EdgeData m_edgeData;
    
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

    virtual math::pimatrix Forward();
    
    virtual void Backward(math::pimatrix& derivatives);
    
    virtual void UpdateParams(int iStep, int batchSize);
    
    /*************************************************************************/
    
    virtual void MergeEdgeData(const EdgeData& edgeData);
    
    virtual void MergeHyperparams(const Hyperparams& hyp);
    
    virtual void ToEdgeData(EdgeData& edgeData);
    
};

}

#endif	/* EDGE_H */

