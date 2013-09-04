/* 
 * File:   InputNode.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 6:11 PM
 */

#ifndef INPUTNODE_H
#define	INPUTNODE_H

#include <Node.h>

namespace model
{

class InputNode : public Node
{
public:
    InputNode();
    InputNode(const InputNode& orig);
    virtual ~InputNode();
    
    math::pimatrix* Forward()
    {
        return NULL;
    }

private:

};

}

#endif	/* INPUTNODE_H */

