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
protected:
    std::vector<std::string> m_files;
    math::pimatrix m_leftOver;
    size_t m_iReadingFile;
    bool m_verbose;
    size_t m_iDimension;
    size_t m_dataSize;
    
public:
    
    Disk(bool verbose = true);
    
    virtual ~Disk();

    virtual math::pimatrix Get(size_t sampleCount);

    virtual void Append(std::vector<std::string>& files, size_t size, size_t dimension);
        
    size_t GetDimension()
    {
        return m_iDimension;
    }
    
    size_t GetSize()
    {
        return m_dataSize;
    }
        
protected:
    
    /*
     * Returns the remaining number of rows needed to be filled in dest.
     * Returns 0 means no need to fill it anymore.
     */
    virtual size_t copyLeftOver(math::pimatrix& dest, size_t destStart);
    
    virtual math::pimatrix loadFile(std::string sFile);
    
};

}
#endif      /* DISK_H */