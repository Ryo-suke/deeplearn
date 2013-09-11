/* 
 * File:   test_model.cpp
 * Author: hoaivu_pham
 *
 * Created on Sep 6, 2013, 10:55:58 AM
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "spnet/Spn.h"
#include "deeplearn.pb.h"
#include "util/Util.h"
#include <DataHandler.h>
#include <Util.h>

/*
 * Simple C++ Test Suite
 */

model::Spn* createSimpleSpn()
{
    model::ModelData modelData;
        
    model::SpnData *spnData = model::SpnData::default_instance().New();
    /*
    spnData->set_node_list("[1,7]((0,0,0,0,3,3,4))");
    spnData->set_input_indices("[1,7]((0,1,2,3,-1,-1,-1))");
    spnData->set_adjacency_matrix("[7,7]((0,0,0,0,1,0,0),(0,0,0,0,0,1,0),(0,0,0,0,1,0,0),(0,0,0,0,0,1,0),(0,0,0,0,0,0,1),(0,0,0,0,0,0,1),(0,0,0,0,0,0,0))");
    */
    
    spnData->set_node_list("[1,7]((4,3,3,0,0,0,0))");
    spnData->set_input_indices("[1,7]((-1,-1,-1,0,1,2,3))");
    spnData->set_adjacency_matrix("[7,7]((0,0,0,0,0,0,0),(1,0,0,0,0,0,0),(1,0,0,0,0,0,0),(0,1,0,0,0,0,0),(0,0,1,0,0,0,0),(0,1,0,0,0,0,0),(0,0,1,0,0,0,0))");
    
    modelData.set_model_type(model::ModelData::SPN);
    modelData.set_name("simple_spn");
    modelData.set_allocated_spn_data(spnData);
    
    return (model::Spn*)model::Model::FromModelData(modelData);
}

void testSpn()
{
    model::Spn* spn = createSimpleSpn();
    BOOST_ASSERT_MSG(spn, "Couldn't create Spn (createSimpleSpn)");
    
    bool sorted = spn->Validate();
    if (!sorted)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testSortNodes (test_model) message=spn->Validate() failed" << std::endl;
    }
    spn->PrintBackpropOrder(std::cout);
    
    delete spn;
}

/*****************************************************************************/

void testDataHandler()
{
    model::DatasetInfo datasetInfo;
    std::string sProtoFile("./tests/data1/data1.pbtxt");
    if(!util::Util::LoadProto(sProtoFile, &datasetInfo))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testDataHandler (test_model) message=protobuf import failed" << std::endl;
        return;
    }
  
    data::DataHandler *handler1, *handler2;
    
    handler1 = data::DataHandler::GetDataHandler(datasetInfo, false, 42, true);
    handler2 = data::DataHandler::GetDataHandler(datasetInfo, true, 42, true);
    
    if(!handler1 || !handler2)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testDataHandler (test_model) message=GetDataHandler() failed" << std::endl;
    }
    
    // default batch size = 100
    std::cout << handler1->GetDataset(model::DatasetInfo_Data::TRAIN_SET)->GetNumBatches() << std::endl;
    std::cout << handler1->GetDataset(model::DatasetInfo_Data::TEST_SET)->GetNumBatches() << std::endl;
    std::cout << handler1->GetDataset(model::DatasetInfo_Data::EVAL_SET)->GetNumBatches() << std::endl;
    
    delete handler1;
    delete handler2;
}

/*****************************************************************************/

void testSpnForward()
{
    // get Spn
    model::Spn* spn = createSimpleSpn();
    BOOST_ASSERT_MSG(spn, "Couldn't create Spn (createSimpleSpn)");
    
    bool sorted = spn->Validate();
    if (!sorted)
    {
        std::cout << "%TEST_FAILED% time=0 testname=testSpnForward (test_model) message=spn->Validate() failed" << std::endl;
    }
    
    // get dataset
    model::DatasetInfo datasetInfo;
    std::string sProtoFile("./tests/data1/data1.pbtxt");
    
    if (!util::Util::LoadProto(sProtoFile, &datasetInfo))
    {
        std::cout << "%TEST_FAILED% time=0 testname=testSpnForward (test_model) message=protobuf import failed" << std::endl;
        return;
    }
  
    data::DataHandler *handler;
    handler = data::DataHandler::GetDataHandler(datasetInfo, true, 42, true);
    data::Dataset* trainSet = handler->GetDataset(model::DatasetInfo_Data::TRAIN_SET);
    
    trainSet->SetBatchSize(100);
    for (int i = trainSet->GetNumBatches() - 1; i >= 0; --i)
    {
        trainSet->EndLoadNextBatch();
        math::pimatrix *batch = trainSet->GetCurrentBatch();
        math::pimatrix err = spn->Forward(batch);
        for (size_t i = 0; i < batch->size1(); ++i)
        {
            float t = batch->operator()(i, 0) * batch->operator()(i, 2)
                    + batch->operator()(i, 1) * batch->operator()(i, 3);
            if (err(i, 0) != t)
                std::cout << "%TEST_FAILED% time=0 testname=testSpnForward (test_model) message=forward computation failed" << std::endl;
        }
    }
    
    delete handler;
    delete spn;
}

/*****************************************************************************/

int main(int argc, char** argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    std::cout << "%SUITE_STARTING% test_model" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testSpn (test_model)" << std::endl;
    testSpn();
    std::cout << "%TEST_FINISHED% time=0 testSpn (test_model)" << std::endl;

    std::cout << "%TEST_STARTED% testDataHandler (test_model)" << std::endl;
    testDataHandler();
    std::cout << "%TEST_FINISHED% time=0 testDataHandler (test_model)" << std::endl;
    
    std::cout << "%TEST_STARTED% testSpnForward (test_model)" << std::endl;
    testSpnForward();
    std::cout << "%TEST_FINISHED% time=0 testSpnForward (test_model)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
        
    return (EXIT_SUCCESS);
}

