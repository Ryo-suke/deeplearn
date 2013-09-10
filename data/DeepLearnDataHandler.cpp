/* 
 * File:   DeepLearnDataHandler.h
 * Author: hoaivu_pham
 *
 * Created on September 8, 2013, 10:51 AM
 */

#include <DeepLearnDataHandler.h>

#include "Dataset.h"
#include <cmath>

namespace data
{

DeepLearnDataHandler::DeepLearnDataHandler(const model::DatasetInfo& datasetInfo
    , size_t batchSize, bool randomize, int randomSeed, bool verbose)
{
    m_sName = datasetInfo.name();

    std::map<model::DatasetInfo_Data_DataType, float> memoryRatios;
    memoryRatios[model::DatasetInfo_Data::TRAIN_SET] = 0.6f;
    memoryRatios[model::DatasetInfo_Data::EVAL_SET] = 0.2f;
    memoryRatios[model::DatasetInfo_Data::TEST_SET] = 0.2f;
    
    // datasetInfo.main_memory() is in GB
    float memorySize = datasetInfo.main_memory() * 1E9;
    
    for(int i = datasetInfo.data_size() - 1; i >= 0; --i)
    {
        const model::DatasetInfo_Data& dataset = datasetInfo.data(i);
        model::DatasetInfo_Data_DataType dataType = dataset.type();
        
        if (m_datasets.count(dataType) == 0)
        {
            m_datasets[dataType] = 
                    new Dataset(dataset, batchSize
                    , (size_t)std::floor(memoryRatios[dataType] * memorySize)
                    , randomize, randomSeed, verbose);
        }
        else
        {
            m_datasets[dataType]->Append(dataset);
        }
    }
}

DeepLearnDataHandler::~DeepLearnDataHandler()
{
    std::map<model::DatasetInfo_Data_DataType, Dataset*>::iterator it;
    for(it = m_datasets.begin(); it != m_datasets.end(); it++)
    {
        delete (it->second);
    }
    m_datasets.clear();
}

Dataset* DeepLearnDataHandler::GetDataset(model::DatasetInfo_Data_DataType type)
{
    if (m_datasets.count(type) == 0)
        return NULL;
    return m_datasets[type];
}

std::string DeepLearnDataHandler::GetDatasetName()
{
    return m_sName;
}

}