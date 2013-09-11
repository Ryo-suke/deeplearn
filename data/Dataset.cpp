/* 
 * File:   Dataset.h
 * Author: hoaivu_pham
 *
 * Created on September 9, 2013, 10:51 AM
 */

#include <Dataset.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <Disk.h>

#define DEFAULT_BATCH_SIZE 100
namespace data
{

Dataset::Dataset(const model::DatasetInfo_Data& dataInfo
        , size_t capacity
        , bool randomize /*= false*/
        , int randomSeed /*= 42*/
        , bool verbose /*= false*/)
: m_batchSize(DEFAULT_BATCH_SIZE)
{
    std::vector<std::string> files;
    Disk *disk;
    
    disk = new Disk(verbose);
    loadFileNames(dataInfo.file_pattern(), files);
    disk->Append(files, dataInfo.size(), dataInfo.dimensions());
    
    // only support 4-byte atomic types at the moment...
    BOOST_ASSERT_MSG(dataInfo.type_size() == 4
            , "Only 4-byte atomic types are supported");
    m_cache = new Cache(disk, capacity
            , 4, randomize, randomSeed, verbose);
}

Dataset::~Dataset()
{
    delete m_cache;
}

/******************************************************************************/

void Dataset::Append(const model::DatasetInfo_Data& dataInfo)
{
    std::vector<std::string> files;
    
    // only support 4-byte atomic types at the moment...
    BOOST_ASSERT_MSG(dataInfo.type_size() == 4
            , "Only 4-byte atomic types are supported");
    loadFileNames(dataInfo.file_pattern(), files);
    m_cache->Append(files, dataInfo.size(), dataInfo.dimensions());
}

math::pimatrix* Dataset::GetCurrentBatch()
{
    return &m_currentBatch;
}

void Dataset::BeginLoadNextBatch()
{
    // do nothing
}

void Dataset::EndLoadNextBatch()
{
    // actually load
    m_currentBatch = m_cache->Get(m_batchSize);
}
    
void Dataset::AllocateMemory()
{
    // do nothing
}

void Dataset::SetBatchSize(size_t nSamples)
{
    m_batchSize = nSamples;
}

int Dataset::GetNumBatches()
{
    size_t n = m_cache->GetSize() / m_batchSize;
    return (m_cache->GetSize() % m_batchSize == 0 ? n : n+1);
}
    
/***************************************************************************/

void Dataset::loadFileNames(const std::string sFilePattern
    , std::vector<std::string>& filesOut)
{
    filesOut.clear();
    
    namespace bf = boost::filesystem;

    bf::path pathPattern(sFilePattern);
    std::string filePath = pathPattern.parent_path().generic_string();;

    boost::regex pattern(pathPattern.leaf().generic_string());

    for (bf::directory_iterator iter(filePath), end; iter != end; ++iter)
    {
        std::string name = (*iter).path().leaf().generic_string();
        if (boost::regex_match(name, pattern))
        {
           filesOut.push_back((*iter).path().generic_string());
        }   
    }
    std::sort(filesOut.begin(), filesOut.end());
}

}
