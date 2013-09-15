/* 
 * File:   Cache.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 9, 2013, 3:17 PM
 */

#include "Cache.h"

namespace data
{

Cache::Cache(Disk* dataProvider, size_t capacity
        , size_t type_size, bool randomize, int randomSeed, bool verbose)
: m_dataProvider(dataProvider)
, m_capacity(capacity)
, m_typeSize(type_size)
, m_bVerbose(verbose)
, m_bRandomize(randomize)
, m_rndGenerator(randomSeed)
{
    BOOST_ASSERT_MSG(dataProvider, "Disk can not be null.");
    AllocateMemory();
}

Cache::~Cache()
{
    delete m_dataProvider;
}

/*****************************************************************************/

math::pimatrix Cache::Get(size_t sampleCount)
{
    math::pimatrix mRet(sampleCount, m_dataProvider->GetDimension());
    size_t copied = 0;
    
    while(copied < sampleCount)
    {
        // request more data
        if (m_currentRow >= m_data.size1())
        {
            m_dataProvider->Get(m_data.size1(), m_data);
            m_currentRow = 0;
            if (m_bRandomize)
                m_data.shuffleRows(m_rndGenerator);
        }
        
        size_t remainingCache = m_data.size1() - m_currentRow;
        size_t remainingCopy = sampleCount - copied;
        size_t copyingRows = std::min(remainingCache, remainingCopy);
        
        mRet.copyRows(m_data, m_currentRow, copyingRows, copied);
        copied += copyingRows;
        m_currentRow += copyingRows;
    }
    return mRet;
}

size_t Cache::GetSize()
{
    return m_dataProvider->GetSize();
}

void Cache::Append(std::vector<std::string>& files, size_t size, size_t dimension)
{
    m_dataProvider->Append(files, size, dimension);
    AllocateMemory();
}

/******************************************************************************/

void Cache::AllocateMemory()
{
    size_t numRow = m_dataProvider->GetSize();
    size_t dim = m_dataProvider->GetDimension();

    if (numRow == 0 || dim == 0)
        return;
        
    size_t maxRowCount = m_capacity / (dim * m_typeSize);
    numRow = (numRow < maxRowCount ? numRow : maxRowCount);
    m_data.resize(numRow, dim);
    m_currentRow = numRow;
}

}