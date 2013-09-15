/* 
 * File:   Dataset.h
 * Author: hoaivu_pham
 *
 * Created on September 6, 2013, 5:13 PM
 */

#ifndef DATASET_H
#define	DATASET_H

#include <boost/noncopyable.hpp>
#include <string>
#include <vector>
#include <Cache.h>
#include <deeplearn.pb.h>

namespace data
{

class Dataset : boost::noncopyable
{
    Cache *m_cache;
    size_t m_batchSize;
    math::pimatrix m_currentBatch;    

public:
    Dataset(size_t capacity
            , bool randomize = false
            , int randomSeed = 42, bool verbose = false);
    
    virtual ~Dataset();
    
    virtual void Append(const model::DatasetInfo& dataInfo, const std::string &sPathPrefix);
    
    virtual math::pimatrix* GetCurrentBatch();
    virtual void BeginLoadNextBatch();
    virtual void EndLoadNextBatch();
    
    virtual void AllocateMemory();
    
    virtual void SetBatchSize(size_t nSamples);
    
    virtual int GetNumBatches();
        
protected:
    void loadFileNames(const std::string sFilePattern
    , std::vector<std::string>& filesOut, const std::string &sPathPrefix);
};

}
#endif	/* DATASET_H */

