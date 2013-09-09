/* 
 * File:   Cache.h
 * Author: hoaivu_pham
 *
 * Created on September 8, 2013, 5:13 PM
 */

#ifndef CACHE_H
#define CACHE_H

#include <boost/noncopyable.hpp>
#include <boost/random/variate_generator.hpp>
#include <string>
#include <pimatrix.h>
#include <Disk.h>

namespace data
{

class Cache : boost::noncopyable
{
    Disk* m_dataProvider;
    size_t m_capacity;
    size_t m_typeSize;
    bool m_bVerbose, m_bRandomize;
    math::pimatrix m_data;
    size_t m_currentRow;                // current row in m_data
    boost::minstd_rand m_rndGenerator;
    
public:
    /*
     * capacity: amount of data, in bytes
     */
    Cache(Disk* dataProvider, size_t capacity
            , size_t type_size = 4
            , bool randomize = false, int randomSeed = 42, bool verbose = false);

    virtual ~Cache();

    virtual math::pimatrix Get(size_t sampleCount);

    virtual size_t GetSize();
    
    virtual void Append(std::vector<std::string>& files, size_t size, size_t dimension);
};

}
#endif      /* CACHE_H */