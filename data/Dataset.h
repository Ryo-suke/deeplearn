/* 
 * File:   Dataset.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 10:51 AM
 */

#ifndef DATASET_H
#define	DATASET_H

#include <pimatrix.h>

namespace data
{

class Dataset
{
protected:
    math::pimatrix* m_currentBatch;
    int m_iBatchSize;
    bool m_bGetLastPiece;
    
public:
    Dataset()
     : m_currentBatch(NULL)
     , m_iBatchSize(1)
     , m_bGetLastPiece(true)
    {    }
     
    Dataset(const Dataset& orig)
    : m_currentBatch(orig.m_currentBatch)
     , m_iBatchSize(orig.m_iBatchSize)
     , m_bGetLastPiece(orig.m_bGetLastPiece)
    {   }
    
    virtual ~Dataset()
    {
        if (m_currentBatch)
            delete m_currentBatch;
    }
    
    /******************************************************************/
    
    virtual math::pimatrix* GetBatch() = 0;
    
    virtual std::string GetDatasetName() = 0;
    
    virtual void AllocateMemory() = 0;
    
    /******************************************************************/
    
    void SetBatchSize(int batchSize)
    {
        m_iBatchSize = batchSize;
        AllocateMemory();
    }
    
    int GetBatchSize()
    {
        return m_iBatchSize;
    }
    
    void SetUseLastPiece(bool getLastPiece)
    {
        m_bGetLastPiece = getLastPiece;
    }
    
    bool GetUseLastPiece()
    {
        return m_bGetLastPiece;
    }
    
private:

};

}
#endif	/* DATASET_H */

