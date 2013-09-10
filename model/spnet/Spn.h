/* 
 * File:   spn.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 5:34 PM
 */

#ifndef SPN_H
#define	SPN_H

#include <deeplearn.pb.h>
#include <pimatrix.h>
#include <Model.h>

namespace model
{

class Spn : public Model
{
    // views on the underlying list of nodes (in Model)
    std::vector<Node*> m_inputNodes, m_hiddenNodes, m_queryNodes;
    Node* m_root;

public:
    Spn();
    virtual ~Spn();
    
    math::pimatrix Forward(math::pimatrix* batch);
    void Backward(){}
    void Train(data::DataHandler* dataHandler, Operation& trainOp);
    
	virtual bool Validate();

    static Spn* FromProto(const ModelData& modelData);
    
private:
    void TrainOneBatch(Operation& trainOp
                    , math::pimatrix* batch);
    void Prune();    
    bool stopCondition(const Operation_StopCondition& cond, int iStep);
    
};

}

#endif	/* SPN_H */

