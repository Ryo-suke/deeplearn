/* 
 * File:   test_train.cpp
 * Author: hoaivu_pham
 *
 * Created on Sep 16, 2013, 5:31:05 PM
 */

#include <stdlib.h>
#include <iostream>
#include "spnet/Spn.h"
#include "Util.h"

#ifdef _MSC_VER
#define MAKE_PATH(x)   "../" x
#else
#define MAKE_PATH(x)   "./" x
#endif

/*
 * Simple C++ Test Suite
 */

void trainModel(std::string& sModelFile, std::string& sTrainOpFile
        , std::string sEvalOpFile)
{
    model::ModelData modelData;
    model::Operation trainOp, evalOp;
    
    if(!util::Util::LoadProto(sModelFile, &modelData))
    {
        std::cout << "%TEST_FAILED% time=0 testname=trainSimpleSpn (test_train) message=model proto import failed"
                  << std::endl;
        return;
    }
    if(!util::Util::LoadProto(sTrainOpFile, &trainOp))
    {
        std::cout << "%TEST_FAILED% time=0 testname=trainSimpleSpn (test_train) message=trainOp proto import failed"
                  << std::endl;
        return;
    }
    if(!util::Util::LoadProto(sEvalOpFile, &evalOp))
    {
        std::cout << "%TEST_FAILED% time=0 testname=trainSimpleSpn (test_train) message=evalOp proto import failed"
                  << std::endl;
        return;
    }
    
    model::Model* model = model::Model::FromModelData(modelData);
    if (!model)
    {
        std::cout << "%TEST_FAILED% time=0 testname=trainSimpleSpn (test_train) message=model creation failed"
                  << std::endl;
        return;
    }
    if (!model->Validate())
    {
        std::cout << "%TEST_FAILED% time=0 testname=trainSimpleSpn (test_train) message=model validation failed: no backprop order found"
                  << std::endl;
        return;
    }
    //model->PrintBackpropOrder(std::cout);
    
    model->Train(trainOp, &evalOp);
}

void trainSimpleSpn()
{
    std::string sModelFile(MAKE_PATH("tests/iris/spn_iris.pbtxt"))
            , sTrainOpFile(MAKE_PATH("tests/iris/train.pbtxt"))
            , sEvalOpFile(MAKE_PATH("tests/iris/eval.pbtxt"));
    
    trainModel(sModelFile, sTrainOpFile, sEvalOpFile);
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% test_train" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% trainSimpleSpn (test_train)" << std::endl;
    trainSimpleSpn();
    std::cout << "%TEST_FINISHED% time=0 trainSimpleSpn (test_train)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

