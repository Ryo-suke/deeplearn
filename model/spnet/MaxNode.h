/* 
 * File:   MaxNode.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 12:03 PM
 */

#ifndef MAXNODE_H
#define	MAXNODE_H

#include <Node.h>

namespace model
{

class MaxNode : public Node
{
public:
    MaxNode();
    MaxNode(const MaxNode& orig);
    virtual ~MaxNode();
    
    math::pimatrix* Forward()
    {
        return NULL;
    }

    
private:

};

}
#endif	/* MAXNODE_H */

