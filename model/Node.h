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
    math::pimatrix m_activations;
    math::pimatrix m_bias;

    Node();
    Node(const Node& orig);
    virtual ~Node();
    
public:
    virtual math::pimatrix* Forward() = 0;
    
private:

};
}

#endif	/* NODE_H */

