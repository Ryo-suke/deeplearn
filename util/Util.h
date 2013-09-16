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

    static void WriteProto(const std::string& sFile, google::protobuf::Message* mess);
    
    static data::DataHandler* LoadDataHandler(const std::string& sDataProtoFile
        , bool randomize = false, int random_seed = 42, bool verbose = false);
    
    static void GetLearningRateAndMomentum(int step
                , const model::Hyperparams& hyperParams
                , float& learningRate, float& momentum);
    
    /*
     * Accumulate the newVal and sampleCount into the Metric stored in metrics.
     */
    static void AccumulateMetric(
        model::Metrics& metrics
        , model::Metric_MetricType t, int sampleCount, float newVal );


    /**************************************************************************/

    static void WriteBytes(char* bytes, int len, char *dest);

    static void WriteSize(size_t val, char* arr);

    static void WriteFloat(float val, char* arr);

    static void ReadBytes(char* bytes, int len, char *dest);

    static size_t ReadSize(char *arr);

    static float ReadFloat(char *arr);
    
    static bool is_big_endian();
    
    static void combination(int* c, int n, int p, int x);
};

}

#endif	/* UTIL_H */

