/* 
 * File:   Node.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 2:50 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <pimatrix.h>

namespace model
{

class Node
{
    
protected:
    /*
     * Should be batch_size x node_size
     * node_size: the number of units in this node
     * batch_size: size of the training batch
     */
    math::pimatrix<float> m_activations;
    math::pimatrix<float> m_bias;
    
public:
    Node();
    Node(const Node& orig);
    virtual ~Node();
    
private:

};
}

#endif	/* NODE_H */

