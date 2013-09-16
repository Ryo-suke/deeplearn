/* 
 * File:   Edge.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 3:17 PM
 */

#include "Edge.h"
#include "Util.h"

namespace model
{

Edge::Edge(Node *node1, Node* node2, bool directed)
{
    m_node1 = node1;
    m_node2 = node2;
    m_edgeData.set_directed(directed);
    
    m_weight.resize(m_node1->GetDimension(), m_node2->GetDimension(), false);
    m_weight.setValue(1);
    
    m_node1->AddOutgoingEdge(this);
    m_node2->AddIncomingEdge(this);
    if (!directed)
    {
        m_node1->AddIncomingEdge(this);
        m_node2->AddOutgoingEdge(this);
    }
}

Edge::~Edge()
{
    m_node1 = m_node2 = NULL;
}

/*****************************************************************************/

math::pimatrix Edge::Forward()
{
    BOOST_ASSERT(m_node1);
    math::pimatrix m = m_node1->GetActivations();
    m.mult(m_weight);
    return m;
}

void Edge::Backward(math::pimatrix& derivatives)
{
    // node1_activations: batch_size x node1_dim
    // node1_derivatives: batch_size x node1_dim
    // node2_activations: batch_size x node2_dim
    // derivatives:       batch_size x node2_dim
    // m_derivatives:     node1_dim  x node2_dim
    // m_weight:          node1_dim  x node2_dim
    
    BOOST_ASSERT_MSG(derivatives.size2() == m_node2->GetDimension(),
            "Derivatives should have size (batch_size x m_node2->GetDimension())");
    if (m_derivatives.size1() > 0 && m_derivatives.size2() > 0)
    {
        m_oldDerivatives = m_derivatives;
    }
    m_derivatives = m_node1->GetActivations();
    m_derivatives.mult(derivatives, 1);
    
    math::pimatrix node1_deriv = derivatives;
    node1_deriv.mult(m_weight, 2);
    m_node1->AccumDerivatives(node1_deriv);
}

void Edge::UpdateParams(int iStep, int batchSize)
{
    if (m_derivatives.size1() == 0)
        return;
    
    float learningRate, momentum;
    math::pimatrix delta_w(m_derivatives.size1(), m_derivatives.size2(), 0);
    
    // get learning rate and momentum...
    util::Util::GetLearningRateAndMomentum(iStep, 
            m_edgeData.hyper_params(), learningRate, momentum);
    
    if (m_oldDerivatives.size1() == m_derivatives.size1()
            && m_oldDerivatives.size2() == m_derivatives.size2())
    {
        delta_w.element_add(m_oldDerivatives, momentum);
    }
    delta_w.element_add(m_derivatives);
    
    m_weight.element_add(delta_w, -learningRate/batchSize);
}

void Edge::NormalizeWeights(const math::pimatrix& matSum)
{
    m_weight.element_div(matSum);
}

/*****************************************************************************/

void Edge::MergeEdgeData(const EdgeData& edgeData)
{
    m_edgeData.MergeFrom(edgeData);
    
    if (m_edgeData.has_weight())
    {
        m_weight.FromString(m_edgeData.weight());
                
        BOOST_ASSERT_MSG(m_weight.size1() == m_node1->GetDimension()
                && m_weight.size2() == m_node2->GetDimension(),
                "Invalid dimensions of the weight matrix");
    }
}

void Edge::MergeHyperparams(const Hyperparams& hyp)
{
    Hyperparams *newHyp = Hyperparams::default_instance().New();
    newHyp->MergeFrom(hyp);
    newHyp->MergeFrom(m_edgeData.hyper_params());
    m_edgeData.set_allocated_hyper_params(newHyp);
}

void Edge::ToEdgeData(EdgeData& edgeData)
{
    edgeData.MergeFrom(m_edgeData);
    edgeData.set_node1(m_node1->GetName());
    edgeData.set_node2(m_node2->GetName());
    edgeData.set_weight(m_weight.ToString());
}

}
