/* 
 * File:   Dataset.h
 * Author: hoaivu_pham
 *
 * Created on September 5, 2013, 10:51 AM
 */

#ifndef DATAHANDLER_H
#define	DATAHANDLER_H

#include <boost/noncopyable.hpp>
#include <pimatrix.h>
#include <deeplearn.pb.h>
#include <Dataset.h>

namespace data
{

class DataHandler : boost::noncopyable
{
protected:
    DataHandler()
    {}

public:
    virtual ~DataHandler()
    {}

    /******************************************************************/
public:

    virtual Dataset* GetDataset(model::DatasetInfo::DataType type) = 0;

    virtual std::string GetDatasetName() = 0;
    
    /******************************************************************/

    static DataHandler* GetDataHandler(const model::DatabaseInfo& databaseInfo
    , bool randomize, int randomSeed, bool verbose);
};

}
#endif	/* DATAHANDLER_H */

