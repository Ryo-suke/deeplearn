/* 
 * File:   InputNode.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 6:11 PM
 */

#ifndef INPUTNODE_H
#define	INPUTNODE_H

#include <boost/assert.hpp>
#include <Node.h>

namespace model
{

class InputNode : public Node
{
public:
    InputNode(NodeData& nodeData);
    InputNode(const InputNode& orig);
    virtual ~InputNode();
    
    /***********************************************************************/
    
    math::pimatrix* Forward()
    {
        return NULL;
    }

    /***********************************************************************/
    
    /*
     * Only for Input nodes, Nx1 matrix, where N = number of dimensions
     */
    virtual void SetValue(math::pimatrix& values)
    {
        BOOST_ASSERT_MSG(values.size1() == m_nodeData.dimension()
                && values.size2() == 1,
                "Invalid dimension");
        m_activations.SetColumns(values);
    }
    
    /*
     * Only for Input nodes, when dimension of this node is 1.
     */
    virtual void SetValue(float value)
    {
        BOOST_ASSERT_MSG(m_nodeData.dimension() == 1,
             "SetValue() with scalar value is only valid with dimension = 1");
        m_activations.SetValue(value);
    }
    
private:

};

}

#endif	/* INPUTNODE_H */

