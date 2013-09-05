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
    std::vector<Node*> m_nodes;
    std::vector<Edge*> m_edges;
    
    /*
     * The list of nodes after topological sorting
     */
    std::vector<Node*> m_nodeList;
    
protected:
    Model();
    Model(std::vector<Node*> &nodes, std::vector<Edge*> &edges);
    Model(const Model& orig);
    virtual ~Model();
    
public:
    virtual math::pimatrix Forward() = 0;
    virtual void Backward() = 0;
    virtual void Train() = 0;
    
    /*
     * Run a topological sort on nodes, detect loop if there is any.
     */
    virtual bool SortNodes();
    
private:

};

}
#endif	/* MODEL_H */

