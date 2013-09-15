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

Dataset::Dataset(size_t capacity
        , bool randomize /*= false*/
        , int randomSeed /*= 42*/
        , bool verbose /*= false*/)
: m_batchSize(DEFAULT_BATCH_SIZE)
{
    m_cache = new Cache(new Disk(verbose), capacity
            , 4, randomize, randomSeed, verbose);
}

Dataset::~Dataset()
{
    delete m_cache;
}

/******************************************************************************/

void Dataset::Append(const model::DatasetInfo& dataInfo, const std::string &sPathPrefix)
{
    std::vector<std::string> files;
    
    // only support 4-byte atomic types at the moment...
    BOOST_ASSERT_MSG(dataInfo.type_size() == 4
        , "Only 4-byte atomic types are supported");
    loadFileNames(dataInfo.file_pattern(), files, sPathPrefix);
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
    , std::vector<std::string>& filesOut, const std::string& sPathPrefix)
{
    namespace bf = boost::filesystem;

    filesOut.clear();
    
    bf::path pathPattern(sFilePattern);

    if (sPathPrefix.size() > 0)
    {
        pathPattern = bf::path(sPathPrefix) / pathPattern;
    }

    std::string filePath = pathPattern.parent_path().generic_string();
    boost::regex pattern(pathPattern.leaf().generic_string());
    
    if(!bf::exists(filePath))
    {
        std::cout << "Invalid file pattern: " << sFilePattern << std::endl;
        return;
    }

    for (bf::directory_iterator iter(filePath), end; iter != end; ++iter)
    {
        std::string name = (*iter).path().leaf().generic_string();
        if (boost::regex_match(name, pattern))
        {
           filesOut.push_back((*iter).path().generic_string());
        }   
    }
    std::sort(filesOut.begin(), filesOut.end());

    if (filesOut.size() == 0)
    {
        std::cout << "Could not find any file satisfied the pattern: "
                  << sFilePattern << std::endl;
    }
}

}
