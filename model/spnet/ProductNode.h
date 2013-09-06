/* 
 * File:   ProductNode.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 12:03 PM
 */

#ifndef PRODUCTNODE_H
#define	PRODUCTNODE_H

#include <Node.h>

namespace model
{

class ProductNode : public Node
{
public:
    ProductNode(NodeData& nodeData);
    virtual ~ProductNode();
    
    math::pimatrix* Forward()
    {
        return NULL;
    }
        
private:

};

}
#endif	/* PRODUCTNODE_H */

