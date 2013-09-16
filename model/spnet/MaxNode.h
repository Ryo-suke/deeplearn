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
    MaxNode(const NodeData& nodeData);
    
    virtual ~MaxNode();
    
    virtual void Forward();

    virtual void Backward();
    
    virtual void NormalizeIncomingEdges();
    
private:

};

}
#endif	/* MAXNODE_H */

