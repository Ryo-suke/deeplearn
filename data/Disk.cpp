/* 
 * File:   Disk.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 9, 2013, 3:17 PM
 */

#include "Disk.h"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace data
{

Disk::Disk(bool verbose /*= true*/)
: m_leftOver(0, 0)
{
    m_verbose = verbose;
    m_iReadingFile = 0;
    m_iDimension = 0;
    m_dataSize = 0;
}

Disk::~Disk()
{   }

/*************************************************************************/

math::pimatrix Disk::Get(size_t sampleCount)
{
    if (m_dataSize == 0 || sampleCount == 0)
        return math::pimatrix(0, 0);
    
    math::pimatrix mRet(sampleCount, m_iDimension);
    size_t iRetStart = 0;

    while(iRetStart < mRet.size1())
    {
        iRetStart = copyLeftOver(mRet, iRetStart);

        if (iRetStart < mRet.size1())
        {
            // load next file
            m_leftOver = loadFile(m_files.at(m_iReadingFile));
            m_iReadingFile = (m_iReadingFile + 1) % m_files.size();
        }
    }
    return mRet;
}

void Disk::Append(std::vector<std::string>& files, size_t size, size_t dimension)
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
        m_files.push_back((*it));
    m_dataSize += size;
}
/****************************************************************************/

/*
 * Returns the remaining number of rows needed to be filled in dest.
 * Returns 0 means no need to fill it anymore.
 */
size_t Disk::copyLeftOver(math::pimatrix& dest, size_t destStart)
{
    size_t iNeedFill = dest.size1() - destStart;

    if (m_leftOver.size1() == 0)
        return destStart;

    if (m_leftOver.size1() > iNeedFill)
    {
        dest.copyRows(m_leftOver, 0, iNeedFill, destStart);
        m_leftOver = m_leftOver.rows(iNeedFill
                , m_leftOver.size1() - iNeedFill);
        return dest.size1();
    }
    else if (m_leftOver.size1() == iNeedFill)
    {
        dest = m_leftOver;
        m_leftOver.resize(0, 0);
        return dest.size1();
    }
    dest.copyRows(m_leftOver, 0, m_leftOver.size1(), 0);
    size_t sNewStart = destStart + m_leftOver.size1();
    m_leftOver.resize(0, 0);
    return sNewStart;
}


math::pimatrix Disk::loadFile(std::string sFile)
{
    if (m_verbose)
    {
        std::cout << "Reading from disk: " << sFile << std::endl;
    }
    math::pimatrix mRet;
    mRet.load(sFile);
    BOOST_ASSERT_MSG(mRet.size2() == m_iDimension, "Invalid data file.");
    return mRet;
}

}