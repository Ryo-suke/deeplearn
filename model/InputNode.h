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
    
    math::pimatrix* Forward()
    {
        return NULL;
    }

    /***********************************************************************/
    
    /*
     * Only for Input nodes, NxM matrix,
     * where N = batch_size, M = number of dimensions in the whole dataset
     */
    virtual void SetValue(math::pimatrix& values)
    {
        BOOST_ASSERT_MSG(values.size2() >= m_nodeData.dimension()
                , "Invalid dimension");
        
        m_activations.CopyRows(values, m_nodeData.input_start_index()
                , values.size1());
    }
    
private:

};

}

#endif	/* INPUTNODE_H */

