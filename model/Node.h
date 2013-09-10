/* 
 * File:   Node.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 2:50 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <boost/noncopyable.hpp>
#include <string>
#include <pimatrix.h>
#include "deeplearn.pb.h"
#include <Edge.h>

namespace model
{
class Edge;

class Node : boost::noncopyable
{
protected:
    /*
     * Should be batch_size x node_size
     * node_size: the number of units in this node
     * batch_size: size of the training batch
     */
    math::pimatrix m_activations;
    
    /*
     * should be 1 x node_size
     */
    math::pimatrix m_bias;
    
    /*
     * batch_size x node_size
     */
    math::pimatrix m_derivatives;
    
    NodeData m_nodeData;
    std::vector<Edge*> m_incomingEdges, m_outgoingEdges;
    
public:
    Node(NodeData& nodeData);
    virtual ~Node();
    
public:
    virtual void Forward() = 0;
    
    virtual void Backward() = 0;
    
    /*
     * Initialize all the derivative to zeros
     */
    virtual void InitializeDerivative(size_t nSamples)
    {
        m_derivatives.resize(nSamples, GetDimension());
        m_derivatives.setValue(0);
    }

    /*
     * Accumulate derivatives wrt output of this node
     * derivative should be a (batch_size x node_size) matrix, 
     * where node_size is the number of units in this node.
     */
    virtual void AccumDerivatives(math::pimatrix& derivative)
    {
        m_derivatives += derivative;
    }
    
    virtual void UpdateParams()
    {
        // do nothing by default.
        // Normally this is only implemented in nodes
        // which contain biases.
    }
    
    /*************************************************************************/
    
    virtual void AddIncomingEdge(Edge* e)
    {
        if (std::find(m_incomingEdges.begin(), m_incomingEdges.end(), e)
                == m_incomingEdges.end())
        {
            m_incomingEdges.push_back(e);
        }
    }
    virtual void AddOutgoingEdge(Edge* e)
    {
        if (std::find(m_incomingEdges.begin(), m_incomingEdges.end(), e)
                == m_incomingEdges.end())
        {
            m_outgoingEdges.push_back(e);
        }
    }
    
    virtual std::string GetName()
    {
        return m_nodeData.name();
    }
    
    virtual size_t GetDimension()
    {
        return (size_t)m_nodeData.dimension();
    }
    
    virtual size_t GetInputStartIndex()
    {
        BOOST_ASSERT_MSG(false, "This operation is only valid for InputNode.");
    }
    
    virtual std::vector<Edge*>& GetIncomingEdges()
    {
        return m_incomingEdges;
    }
        
    virtual size_t GetIncomingEdgesCount()
    {
        return m_incomingEdges.size();
    }
    
    virtual std::vector<Edge*>& GetOutgoingEdges()
    {
        return m_outgoingEdges;
    }

    virtual size_t GetOutgoingEdgesCount()
    {
        return m_outgoingEdges.size();
    }
    
    virtual math::pimatrix& GetActivations()
    {
        return m_activations;
    }

    /*
     * Only for Input nodes
     */
    virtual void SetValue(math::pimatrix& values)
    {    }

    /*
     * Only for Input nodes
     */
    virtual void SetValue(float val, size_t sampleCount)
    {    }
    
private:

};
}

#endif	/* NODE_H */

