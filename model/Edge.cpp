/* 
 * File:   Edge.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 4, 2013, 3:17 PM
 */

#include "Edge.h"

namespace model
{

Edge::Edge(Node *node1, Node* node2, bool directed)
{
    m_node1 = node1;
    m_node2 = node2;
    m_bDirected = directed;
    
    m_weight.resize(m_node1->GetDimension(), m_node2->GetDimension(), false);
    m_weight.setValue(1);
    
    m_node1->AddOutgoingEdge(this);
    m_node2->AddIncomingEdge(this);
    if (!m_bDirected)
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
    m_derivatives = m_node1->GetActivations();
    m_derivatives.mult(derivatives, 1);
    
    math::pimatrix node1_deriv = derivatives;
    node1_deriv.mult(m_weight, 2);
    m_node1->AccumDerivatives(node1_deriv);
}

void Edge::UpdateParams()
{
    if (m_derivatives.size1() == 0)
        return;
    
    // get learning rate
    float learningRate = 0.0001;
    m_weight.element_add(m_derivatives, -learningRate);
}

}
