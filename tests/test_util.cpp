/* 
 * File:   test_util.cpp
 * Author: hoaivu_pham
 *
 * Created on Sep 9, 2013, 10:55:58 AM
 */

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>
#include <boost/random.hpp>
#include <string>
#include <iostream>
#include <pimatrix.h>

#include "deeplearn.pb.h"

void loadFileNames(const std::string sFilePattern)
{
    namespace bf = boost::filesystem;

    bf::path pathPattern(sFilePattern);
    std::string filePath = pathPattern.parent_path().generic_string();;

    boost::regex pattern(pathPattern.leaf().generic_string());
    std::vector<std::string> accumulator;
    
    for (bf::directory_iterator iter(filePath), end; iter != end; ++iter)
    {
        std::string name = (*iter).path().leaf().generic_string();
        if (boost::regex_match(name, pattern))
        {
           accumulator.push_back((*iter).path().generic_string());
        }   
    }
    std::sort(accumulator.begin(), accumulator.end());
    for (std::vector<std::string>::iterator it = accumulator.begin();
            it != accumulator.end(); ++it)
    {
        std::cout << (*it) << std::endl;
    }
}

void testLoadFiles()
{
    std::string sPattern = "/etc/X11/xorg.*";
    std::cout << sPattern << std::endl;
    loadFileNames(sPattern);
    
    sPattern = "/etc/X11/[a-zA-Z]*.conf";
    std::cout << std::endl << sPattern << std::endl;
    loadFileNames(sPattern);
}

/*****************************************************************************/

void testBoostMatrix()
{
    std::string sMat("[3,2]((1.2,2),(-3.4,-2.39E-5),(-3.14E-1, 0.0))");
    std::string sFile("../tmpMatrix.m");
    
    math::pimatrix m;
    m.FromDebugString(sMat);
    m.save(sFile);
    
    math::pimatrix m2;
    m2.load(sFile);
    
    std::cout << "Begin serialization: " << std::endl << m << std::endl
            << "After serialization: " << std::endl << m2 << std::endl;
    
    m.setValue(-10.39);
    std::cout << "After setValue(-10.39): " << std::endl << m << std::endl;
    
    m.copyRows(m2, 0, 1, 0);
    std::cout << "After copyRows(m2, 0, 1, 0): " << std::endl << m << std::endl;
    
    m.setValue(-10.39);
    m.copyRows(m2, 2, 1, 2);
    std::cout << "After copyRows(m2, 2, 1, 2): " << std::endl << m << std::endl;
    
    m.setValue(2);
    m.dot(m2);
    std::cout << "After dot(m2): " << std::endl << m << std::endl;
    
    boost::random::minstd_rand gen(42);
    m.shuffleRows(gen);
    std::cout << "After shuffleRows(gen): " << std::endl << m << std::endl;
    
    std::cout << "m.ToString(): " << m.ToString() << std::endl;

    math::pimatrix mBig(200, 200, 10);
    std::cout << "ToString(): " << mBig.ToString().size() << std::endl
              << " ToDebugString(): " << mBig.ToDebugString().size() << std::endl;

    std::string sBigMat = mBig.ToString();
    math::pimatrix mBig2;
    mBig2.FromString(sBigMat);
    for (size_t i = 0; i < mBig2.size1(); ++i)
    {
        for (size_t j = 0; j < mBig2.size2(); ++j)
        {
            BOOST_ASSERT_MSG(mBig2(i,j) == 10, "ToString() is incorrect.");
        }
    }
}

/*****************************************************************************/


void generateData(int rowCount, std::string sFile)
{
    math::pimatrix m(rowCount, 4, 0);
    for (size_t i = 0; i < rowCount; ++i)
    {
        m.set(i, 0, ((float)i)/rowCount);
        m.set(i, 1, 1.0f - ((float)i)/rowCount);
        m.set(i, 2, ((float)i)/rowCount);
        m.set(i, 3, 1.0f - ((float)i)/rowCount);
    }
    m.save(sFile);

    math::pimatrix m2;
    m2.load(sFile);
    for (size_t i = 0; i < m.size1(); ++i)
    {
        for (size_t j = 0; j < m.size2(); ++j)
        {
            BOOST_ASSERT_MSG(m(i,j) == m2(i,j), "generateData() is incorrect.");
        }
    }
}

void generateData()
{
    generateData(600, "../tests/data1/m1.m");
    generateData(200, "../tests/data1/m2.m");
    generateData(200, "../tests/data1/m3.m");
    std::cout << "Generating data done." << std::endl;
}

/*****************************************************************************/

void testProtobufMerge()
{
    model::Hyperparams p1;
    p1.set_base_learningrate(0.002f);
    
    model::Hyperparams p2;
    p2.set_initial_momentum(1.0f);
    p2.set_base_learningrate(0.003f);
    
    p1.MergeFrom(p2);

    if (p1.initial_momentum() != p2.initial_momentum())
    {
        std::cout << "%TEST_FAILED% time=0 testname=testProtobufMerge (test_util) message=Merge failed" << std::endl;
    }
    
    if (p1.final_momentum() != p2.final_momentum())
    {
        std::cout << "%TEST_FAILED% time=0 testname=testProtobufMerge (test_util) message=Merge failed" << std::endl;
    }
}

/*****************************************************************************/

void Foo(std::vector<model::Metric> &v)
{
    model::Metric m;
    m.set_type(model::Metric::CLASSIFICATION_ERROR);
    m.add_steps(1);
    m.add_values(0.2);
    v.push_back(m);
}

void testCpp()
{
    std::vector<model::Metric> v;
    Foo(v);
    std::cout << (*v.begin()).Utf8DebugString() << std::endl;
}

/*****************************************************************************/

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% test_util" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testLoadFiles (test_util)" << std::endl;
    //testLoadFiles();
    std::cout << "%TEST_FINISHED% time=0 testLoadFiles (test_util)" << std::endl;

    std::cout << "%TEST_STARTED% testBoostMatrix (test_util)" << std::endl;
    testBoostMatrix();
    std::cout << "%TEST_FINISHED% time=0 testBoostMatrix (test_util)" << std::endl;
    
    std::cout << "%TEST_STARTED% testProtobufMerge (test_util)" << std::endl;
    testProtobufMerge();
    std::cout << "%TEST_FINISHED% time=0 testProtobufMerge (test_util)" << std::endl;
    
    generateData();
    //testCpp();
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;
    std::cin.get();

    return (EXIT_SUCCESS);
}