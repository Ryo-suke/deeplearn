/* 
 * File:   Dataset.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 10:51 AM
 */

#ifndef DATASET_H
#define	DATASET_H

#include <boost/noncopyable.hpp>
#include <pimatrix.h>
#include <deeplearn.pb.h>

namespace data
{

class DataHandler : boost::noncopyable
{
protected:
    model::DatasetInfo m_datasetInfo;
    int m_iBatchSize;
    bool m_bGetLastPiece;
    
protected:
    DataHandler(const model::DatasetInfo& datasetInfo)
        : m_iBatchSize(1)
        , m_bGetLastPiece(true)
    {
        m_datasetInfo = datasetInfo;
    }

    virtual ~DataHandler()
    {
    }

    /******************************************************************/
public:

    virtual std::string GetHandlerName() = 0;
    
    
    virtual math::pimatrix* GetCurrentBatch() = 0;
    virtual void BeginLoadNextBatch() = 0;
    virtual void EndLoadNextBatch() = 0;
    
    virtual void AllocateMemory() = 0;
    
    virtual int GetNumTrainingBatches() = 0;

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
    
    static DataHandler* GetDataHandler(model::DatasetInfo& datasetInfo)
    {
        return NULL;
    }
    
private:

};

}
#endif	/* DATASET_H */

