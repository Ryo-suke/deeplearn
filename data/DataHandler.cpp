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

DataHandler* DataHandler::GetDataHandler(const model::DatabaseInfo& databaseInfo
    , bool randomize, int randomSeed, bool verbose)
{
    std::string sName = databaseInfo.data_handler();

    if (sName.compare(DeepLearnDataHandler::GetHandlerName()) == 0)
    {
        return new DeepLearnDataHandler(databaseInfo
                , randomize, randomSeed, verbose);
    }
    return NULL;
}
}