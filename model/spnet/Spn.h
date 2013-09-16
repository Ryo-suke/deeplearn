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
    void Backward();
    void Train(Operation& trainOp, Operation* evalOp = NULL);
    virtual void Evaluate(Operation& evalOp, data::Dataset* evalDataset
        , model::Metrics &evalStats);

    virtual bool Validate();
    
private:
    
    void TrainOneBatch(Operation& trainOp
                    , math::pimatrix* batch, int iTrainStep
                    , Metrics *metrics);
    
    void Prune();
    
    bool stopCondition(const Operation_StopCondition& cond, int iStep);
    bool evalCondition(int eval_after, int iStep);
    bool checkpointCondition(int checkpoint_after, int iStep);
    
    /*
     * Append newMetric (after taking average) to metrics
     */
    void appendStats(Metrics* metrics, Metrics &newMetrics, int iTrainStep);
    
    void normalizeWeights();
    
public:
    static Spn* FromProto(const ModelData& modelData);

private:
    static bool LoadSpnInit(const SpnData& spnData
                , std::vector<Node*>& nodes, std::vector<Edge*>& edges);
    static bool LoadSpnLayerInit(const SpnData& spnData
                , std::vector<Node*>& nodes, std::vector<Edge*>& edges);
    static bool LoadSpnListInit(const SpnData& spnData
                , std::vector<Node*>& nodes, std::vector<Edge*>& edges);
    
    static bool LoadSpnStructure(const ModelData& modelData
                , std::vector<Node*>& nodes, std::vector<Edge*>& edges);
    
    static Node* CreateNewNode(const NodeData& nodeData);
    
    static bool CreateLayer(const SpnLayerInit& layerInit
                , std::vector<Node*>& lowerLayer
                , std::vector<Node*>& newNodes, std::vector<Edge*>& newEdges);
    static bool CreateInputLayer(const SpnLayerInit& layerInit
                , std::vector<Node*>& newNodes, std::vector<Edge*>& newEdges);
    static bool CreateSumMaxLayer(const SpnLayerInit& layerInit
                , std::vector<Node*>& lowerLayer
                , std::vector<Node*>& newNodes, std::vector<Edge*>& newEdges);
    static bool CreateProductLayer(const SpnLayerInit& layerInit
                , std::vector<Node*>& lowerLayer
                , std::vector<Node*>& newNodes, std::vector<Edge*>& newEdges);
};

}

#endif	/* SPN_H */

