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

namespace data
{

class DeepLearnDataHandler : public DataHandler
{

public:
    DeepLearnDataHandler(const model::DatasetInfo& datasetInfo);

    virtual ~DeepLearnDataHandler();

};

}

#endif