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
    SumNode(const NodeData& nodeData);
    
    virtual ~SumNode();
    
    virtual void Forward();
    
    virtual void Backward();
    
    virtual void NormalizeIncomingEdges();
    
private:

};

}
#endif	/* SUMNODE_H */

