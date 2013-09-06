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
#include <deeplearn.pb.h>
#include <DataHandler.h>

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
    
    std::string m_modelName;
    
protected:
    Model();
    Model(const std::string& modelName
            , std::vector<Node*> &nodes
            , std::vector<Edge*> &edges);
    Model(const Model& orig);
    virtual ~Model();
    
public:
    virtual math::pimatrix Forward() = 0;
    virtual void Backward() = 0;
    virtual void Train(data::DataHandler* dataHandler, Operation& trainOp) = 0;
    
    /*
     * Run a topological sort on nodes, detect loop if there is any.
     */
    virtual bool SortNodes();
    virtual void PrintBackpropOrder(std::ostream& s);
    
    static Model* FromModelData(const ModelData& modelData);
    
protected:
    
    template <typename T>
    static void deleteList(const std::vector<T*>& vList);

};

}
#endif	/* MODEL_H */

