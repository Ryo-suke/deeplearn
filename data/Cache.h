/* 
 * File:   Cache.h
 * Author: hoaivu_pham
 *
 * Created on September 8, 2013, 5:13 PM
 */

#ifndef CACHE_H
#define CACHE_H

#include <boost/noncopyable.hpp>
#include <string>
#include <pimatrix.h>

namespace data
{

class Cache : boost::noncopyable
{

public:
    Cache(const std::string sFilePattern)
    {

    }

    virtual ~Cache()
    {

    }

    virtual math::pimatrix Get(int sampleCount)
    {
        return math::pimatrix();
    }

};

}
#endif      /* CACHE_H */