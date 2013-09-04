/* 
 * File:   Model.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 3:10 PM
 */

#ifndef MODEL_H
#define	MODEL_H

#include <vector>
#include <Node.h>
#include <Edge.h>

namespace model
{

class Model
{
protected:
    std::vector<Node> m_nodes;
    std::vector<Edge> m_edges;
    
public:
    Model();
    Model(const Model& orig);
    virtual ~Model();
    
private:

};

}
#endif	/* MODEL_H */

