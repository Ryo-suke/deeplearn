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
    virtual ~InputNode();
    
    /***********************************************************************/
    
    virtual void Forward()
    {
        // doing nothing
    }

    /***********************************************************************/
    
    /*
     * Only for Input nodes, NxM matrix,
     * where N = batch_size, M = number of dimensions in the whole dataset
     */
    virtual void SetValue(math::pimatrix& values)
    {
        size_t dim = GetDimension();
        BOOST_ASSERT_MSG(values.size2() >= dim
                , "Invalid dimension");
        
        if (m_activations.size1() != values.size1() 
            || m_activations.size2() != dim)
        {
            m_activations.resize(values.size1(), dim);
        }

        m_activations.copyColumns(values, m_nodeData.input_start_index()
                , dim);
    }
    
    virtual void SetValue(float val)
    {
        m_activations.setValue(val);
    }

private:

};

}

#endif	/* INPUTNODE_H */

