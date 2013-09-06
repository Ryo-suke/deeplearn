/* 
 * File:   SumNode.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 12:03 PM
 */

#ifndef SUMNODE_H
#define	SUMNODE_H

#include <Node.h>

namespace model
{

class SumNode : public Node
{
public:
    SumNode(NodeData& nodeData);
    virtual ~SumNode();
    
    math::pimatrix* Forward()
    {
        return NULL;
    }
        
private:

};

}
#endif	/* SUMNODE_H */

