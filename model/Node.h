/* 
 * File:   Node.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 2:50 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <string>
#include <pimatrix.h>

#include "deeplearn.pb.h"

#include <Edge.h>

namespace model
{
class Edge;

class Node
{
protected:
    /*
     * Should be batch_size x node_size
     * node_size: the number of units in this node
     * batch_size: size of the training batch
     */
    math::pimatrix m_activations, m_bias;
    NodeData m_nodeData;
    std::vector<Edge*> m_incomingEdges, m_outgoingEdges;
    
public:
    Node(NodeData& nodeData);
    Node(const Node& orig);
    virtual ~Node();
    
public:
    virtual void Forward() = 0;
    
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
    virtual void SetValue(float val)
    {    }
    
private:

};
}

#endif	/* NODE_H */

