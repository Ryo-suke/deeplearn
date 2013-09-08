/* 
 * File:   Disk.h
 * Author: hoaivu_pham
 *
 * Created on September 8, 2013, 5:13 PM
 */

#ifndef DISK_H
#define DISK_H

#include <boost/noncopyable.hpp>
#include <string>
#include <pimatrix.h>

namespace data
{

class Disk : boost::noncopyable
{
    std::vector<std::string> m_files;
    math::pimatrix m_leftOver;

public:
    Disk(const std::string sFilePattern)
    {

    }

    virtual ~Disk()
    {

    }

    virtual math::pimatrix Get(int sampleCount)
    {
        return math::pimatrix();
    }

};

}
#endif      /* DISK_H */