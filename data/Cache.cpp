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
    
    size_t dim = m_dataProvider->GetDimension();
    size_t numRow = capacity / (dim * m_typeSize);
    m_data.resize(numRow, dim);
    m_currentRow = numRow;
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
        size_t remainingCache = m_data.size1() - m_currentRow;
        size_t remainingCopy = sampleCount - copied;
        if (remainingCache > remainingCopy)
        {
            mRet.copyRows(m_data, m_currentRow, remainingCopy, copied);
            copied += remainingCopy;
            m_currentRow += remainingCopy;
        }
        else
        {
            mRet.copyRows(m_data, m_currentRow, remainingCache, copied);
            copied += remainingCache;
            m_currentRow += remainingCache;
        }
        
        // request more data
        if (m_currentRow >= m_data.size1())
        {
            m_data = m_dataProvider->Get(m_data.size1());
            if (m_bRandomize)
                m_data.shuffleRows(m_rndGenerator);
        }
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
}

}