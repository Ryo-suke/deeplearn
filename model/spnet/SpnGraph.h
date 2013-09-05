/* 
 * File:   SpnGraph.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 11:16 AM
 */

#ifndef SPNGRAPH_H
#define	SPNGRAPH_H

#include <vector>
#include <string>
#include <pimatrix.h>

namespace model
{

class SpnGraph
{
public:
    enum SpnNodeType
    {
        SPN_NODE_INPUT,
        SPN_NODE_SUM,
        SPN_NODE_PRODUCT,
        SPN_NODE_MAX
    };

    /*
     * A 1xN matrix containing N nodes, each item takes value from SpnNodeType
     */
    math::pimatrix m_nodeList;
    /*
     * m_adjacencyMatrix(i, j) != 0: there is an edge from i to j
     */
    math::pimatrix m_adjacencyMatrix;
    int m_iRootNode;
    
    SpnGraph(std::string sFilePath);
    SpnGraph(const SpnGraph& orig);
    virtual ~SpnGraph();
    
private:

};

}
#endif	/* SPNGRAPH_H */

