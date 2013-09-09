/* 
 * File:   DeepLearnDataHandler.h
 * Author: hoaivu_pham
 *
 * Created on September 8, 2013, 10:51 AM
 */

#ifndef DEEPLEARN_DATAHANDLER_H
#define	DEEPLEARN_DATAHANDLER_H

#include <DataHandler.h>
#include <deeplearn.pb.h>
#include <pimatrix.h>
#include <map>

namespace data
{

class DeepLearnDataHandler : public DataHandler
{
    
    std::map<model::DatasetInfo_Data_DataType, Dataset*> m_datasets;
    std::string m_sName;
    
public:
    DeepLearnDataHandler(const model::DatasetInfo& datasetInfo
        , size_t batchSize, bool randomize, int randomSeed, bool verbose);

    virtual ~DeepLearnDataHandler();
    
    virtual Dataset* GetDataset(model::DatasetInfo_Data_DataType type);
    
    virtual std::string GetDatasetName();
    
    static std::string GetHandlerName()
    {
        return "deeplearn";
    }
};

}

#endif