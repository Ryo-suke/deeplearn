/* 
 * File:   DataHandler.h
 * Author: hoaivu_pham
 *
 * Created on September 9, 2013, 10:51 AM
 */

#include <DataHandler.h>
#include <DeepLearnDataHandler.h>

namespace data
{

DataHandler* DataHandler::GetDataHandler(const model::DatasetInfo& datasetInfo
    , bool randomize, int randomSeed, bool verbose)
{
    std::string sName = datasetInfo.data_handler();

    if (sName.compare(DeepLearnDataHandler::GetHandlerName()) == 0)
    {
        return new DeepLearnDataHandler(datasetInfo
                , randomize, randomSeed, verbose);
    }
    return NULL;
}
}