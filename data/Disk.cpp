/* 
 * File:   Disk.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 9, 2013, 3:17 PM
 */

#include "Disk.h"
#include "deeplearn.pb.h"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace data
{

Disk::Disk(bool verbose /*= true*/)
: m_currentFile(0, 0)
{
    m_verbose = verbose;
    m_iReadingFile = 0;
    m_iDimension = 0;
    m_dataSize = 0;
    m_currentRow = 0;
}

Disk::~Disk()
{   }

/*************************************************************************/

void Disk::Get(size_t sampleCount, math::pimatrix& matRet)
{
    if (m_dataSize == 0 || sampleCount == 0)
    {
        matRet.resize(0, 0);
        return;
    }    
    
    matRet.resize(sampleCount, m_iDimension);
    size_t copied = 0;
    
    while(copied < sampleCount)
    {
        // request more data
        if (m_currentRow >= m_currentFile.size1())
        {
            if (m_files.size() > 1 || m_currentFile.size1() == 0)
            {
                // only load next file if we have more than 1 file
                // or this is the first file ever read.
                loadFile(m_files.at(m_iReadingFile), m_currentFile
                        , m_fileFormat.at(m_iReadingFile));
                m_iReadingFile = (m_iReadingFile + 1) % m_files.size();
            }
            m_currentRow = 0;
        }
        
        size_t remainingCache = m_currentFile.size1() - m_currentRow;
        size_t remainingCopy = sampleCount - copied;
        size_t copyingRows = std::min(remainingCache, remainingCopy);
        
        matRet.copyRows(m_currentFile, m_currentRow, copyingRows, copied);
        copied += copyingRows;
        m_currentRow += copyingRows;
    }
}

void Disk::Append(std::vector<std::string>& files
    , size_t size, size_t dimension
    , model::DatasetInfo_DataFormat dataFormat)
{
    if (m_iDimension == 0 && m_dataSize == 0)
    {
        m_iDimension = dimension;
    }
    else
    {
        BOOST_ASSERT_MSG(m_iDimension == dimension
                , "Invalid dimension of data files");
    }
    
    for (std::vector<std::string>::iterator it = files.begin(); 
            it != files.end(); it++)
    {
        m_files.push_back((*it));
        m_fileFormat.push_back(dataFormat);
    }
    m_dataSize += size;
}
/****************************************************************************/

void Disk::loadFile(std::string sFile, math::pimatrix& matRet
        , model::DatasetInfo_DataFormat dataFormat)
{
    bool bRet;
    if (m_verbose)
    {
        std::cout << "Reading from disk: " << sFile << std::endl;
    }
    switch(dataFormat)
    {
        case model::DatasetInfo::BOOST_MATRIX:
            bRet = matRet.load(sFile);
            break;
        case model::DatasetInfo::CSV:
            bRet = matRet.loadCsv(sFile);
            break;
    }
    
    BOOST_ASSERT_MSG(bRet && matRet.size2() == m_iDimension
            , "Invalid data file.");
}

}