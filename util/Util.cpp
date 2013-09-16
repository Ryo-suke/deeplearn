/* 
 * File:   Util.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 11, 2013, 11:29 AM
 */

#include "Util.h"

#ifdef _MSC_VER
#include <stdio.h>
#include <io.h>
#else
#include <fcntl.h>
#endif
#include <boost/bind.hpp>
#include <fstream>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace util
{

#ifdef _MSC_VER
    int getFileHandle(const std::string& sFile)
    {
        FILE* f;
        if (fopen_s(&f, sFile.c_str(), "r") != 0)
            return -1;

        return _fileno(f);
    }
    void closeFileHandle(int fileHandle)
    {
        _close(fileHandle);
    }
#else
    int getFileHandle(const std::string& sFile)
    {
        return open(sFile.c_str(), O_RDONLY);
    }
    void closeFileHandle(int fileHandle)
    {
        close(fileHandle);
    }
#endif

bool Util::LoadProto(const std::string& sFile, google::protobuf::Message* mess)
{
    int fileDescriptor = getFileHandle(sFile);
    
    if( fileDescriptor < 0 )
    {
        return false;
    }

    google::protobuf::io::FileInputStream fileInput(fileDescriptor);
    fileInput.SetCloseOnDelete( true );

    bool bRet = google::protobuf::TextFormat::Parse(&fileInput, mess);
    
    // no need to close, google protobuf does that.
    //closeFileHandle(fileDescriptor);
    
    return bRet;
}

void Util::WriteProto(const std::string& sFile, google::protobuf::Message* mess)
{
    std::ofstream ofs(sFile.c_str(), std::ios_base::out | std::ios_base::trunc);

    mess->SerializeToOstream(&ofs);
    ofs.flush();
    ofs.close();
}

data::DataHandler* Util::LoadDataHandler(const std::string& sDataProtoFile
    , bool randomize /*= false*/, int random_seed /*= 42*/, bool verbose /*= false*/)
{
    model::DatabaseInfo databaseInfo;
    if (!util::Util::LoadProto(sDataProtoFile, &databaseInfo))
    {
        std::cout << "ERR\tUnable to load the dataset proto file." << std::endl;
        return NULL;
    }
    data::DataHandler* dataHandler = 
            data::DataHandler::GetDataHandler(databaseInfo, randomize
        , random_seed, verbose);
    
    if (!dataHandler)
    {
        std::cout << "ERR\tUnable to create data handler." << std::endl;
    }
    return dataHandler;
}

/*****************************************************************************/

void Util::GetLearningRateAndMomentum(int step, const model::Hyperparams& hyperParams
                , float& learningRate, float& momentum)
{
    momentum = hyperParams.final_momentum() - (hyperParams.final_momentum() 
            - hyperParams.initial_momentum())
            *std::exp(-float(step)/hyperParams.momentum_change_steps());
    learningRate = hyperParams.base_learningrate();
    
    switch(hyperParams.learningrate_decay())
    {
        case model::Hyperparams::DECAY_INVERSE_T:
            learningRate = hyperParams.base_learningrate() /
                    (1 + float(step) / hyperParams.learningrate_decay_half_life());
            break;
        case model::Hyperparams::DECAY_EXPONENTIAL:
            learningRate = hyperParams.base_learningrate() / 
                    std::pow(2, float(step) / hyperParams.learningrate_decay_half_life());
            break;
    }
}

/******************************************************************************/

void Util::AccumulateMetric(
        model::Metrics& metrics
        , model::Metric_MetricType t, int sampleCount, float newVal)
{
    int i = -1;
    for (i = metrics.metrics_size() - 1; i >= 0; --i)
    {
        if (metrics.metrics(i).type() == t)
        {
            break;
        }
    }
    
    if(i < 0)
    {
        model::Metric *m = metrics.add_metrics();
        m->set_type(t);
        m->add_steps(sampleCount);
        m->add_values(newVal);
        
    }
    else
    {
        model::Metric *mOld = metrics.mutable_metrics(i);
        int idx = mOld->steps_size() - 1;
        mOld->set_steps(idx, mOld->steps(idx) + sampleCount);
        mOld->set_values(idx, mOld->values(idx) + newVal);
    }
    
}

/**************************************************************************/
#define INT_SIZE 4

void Util::WriteBytes(char* bytes, int len, char *dest)
{
    int i;
    if (is_big_endian())
    {
        for(i = 0; i < len; ++i)
            dest[i] = bytes[i];
    }
    else
    {
        for(i = 0; i < len; ++i)
            dest[i] = bytes[len-1-i];
    }
}

void Util::WriteSize(size_t val, char* arr)
{
    char *ptr = (char*) (& val);
    if (sizeof(size_t) != INT_SIZE && is_big_endian())
    {
        ptr += (sizeof(size_t) - INT_SIZE);
    }
    WriteBytes(ptr, INT_SIZE, arr);
}

void Util::WriteFloat(float val, char* arr)
{
    BOOST_ASSERT_MSG(sizeof(float) == INT_SIZE,
            "Unportable because sizeof(float) != 4");
    char *ptr = (char*) (& val);
    WriteBytes(ptr, INT_SIZE, arr);
}

size_t Util::ReadSize(char *arr)
{
    size_t iRet = 0;
    char *ptr = (char*) (& iRet) ;
    if (sizeof(size_t) != INT_SIZE && is_big_endian())
    {
        ptr += (sizeof(size_t) - INT_SIZE);
    }
    ReadBytes(ptr, INT_SIZE, arr);
    return iRet;
}

float Util::ReadFloat(char *arr)
{
    BOOST_ASSERT_MSG(sizeof(float) == INT_SIZE,
            "Unportable because sizeof(float) != 4");
    float fRet = 0;
    char *ptr = (char*) (& fRet) ;
    ReadBytes(ptr, INT_SIZE, arr);
    return fRet;
}

void Util::ReadBytes(char* bytes, int len, char *dest)
{
    int i;
    if (is_big_endian())
    {
        for(i = 0; i < len; ++i)
            bytes[i] = dest[i];
    }
    else
    {
        for(i = 0; i < len; ++i)
            bytes[i] = dest[len-1-i];
    }
}

bool Util::is_big_endian()
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}

/***************************************************************************/

void Util::combination(int* c, int n, int p, int x)
{
    /** [combination c n p x]
     * get the [x]th lexicographically ordered set of [p] elements in [n]
     * output is in [c], and should be sizeof(int)*[p] */
    // http://stackoverflow.com/questions/561/using-combinations-of-sets-as-test-data#794
    int i,r,k = 0;
    for(i=0;i<p-1;i++)
    {
        c[i] = (i != 0) ? c[i-1] : 0;
        do
        {
            c[i]++;
            r = (int)boost::math::binomial_coefficient<float>(n-c[i],p-(i+1));
            k = k + r;
        } 
        while(k < x);
        k = k - r;
    }
    c[p-1] = c[p-2] + x - k;
}

}
