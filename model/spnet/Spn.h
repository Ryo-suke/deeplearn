/* 
 * File:   spn.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 5:34 PM
 */

#ifndef SPN_H
#define	SPN_H

#include <Model.h>
#include <deeplearn.pb.h>

namespace model
{

class Spn : public Model
{
    // views on the cannonical list of nodes
    std::vector<Node*> m_inputNodes, m_hiddenNodes, m_queryNodes;
    
public:
    Spn(std::vector<Node*>& nodes
            , std::vector<Edge*>& edges
            , std::vector<Node*>& inputNodes
            , std::vector<Node*>& hiddenNodes
            , std::vector<Node*>& queryNodes);
    Spn(const Spn& orig);
    virtual ~Spn();
    
    math::pimatrix Forward(){}
    void Backward(){}
    void Train(){}
    
    static Spn* FromProto(const ModelData& modelData);
    
    template <typename T>
    static void deleteList(const std::vector<T*>& vList);
    
};

}

#endif	/* SPN_H */

