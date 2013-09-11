/* 
 * File:   Util.h
 * Author: hoaivu_pham
 *
 * Created on September 11, 2013, 11:29 AM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <boost/noncopyable.hpp>
#include <google/protobuf/message.h>
#include <DataHandler.h>

namespace util
{

class Util : boost::noncopyable
{
protected:
    Util(){}
    virtual ~Util(){}

public:
    
    static bool LoadProto(const std::string& sFile, google::protobuf::Message* mess);

    static data::DataHandler* LoadDataHandler(const std::string& sDataProtoFile
        , bool randomize = false, int random_seed = 42, bool verbose = false);
    
    static void GetLearningRateAndMomentum(int step
                , const model::Hyperparams& hyperParams
                , float& learningRate, float& momentum);
};

}

#endif	/* UTIL_H */

