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
        if (fopen_s(&f, sFile.c_str(), "r") == 0)
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

}
