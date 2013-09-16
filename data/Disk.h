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
#include <deeplearn.pb.h>

namespace data
{

class Disk : boost::noncopyable
{
protected:
    std::vector<std::string> m_files;
    std::vector<model::DatasetInfo_DataFormat> m_fileFormat;
    math::pimatrix m_currentFile;
    size_t m_currentRow;
    size_t m_iReadingFile;
    bool m_verbose;
    size_t m_iDimension;
    size_t m_dataSize;
    
public:
    
    Disk(bool verbose = true);
    
    virtual ~Disk();

    virtual void Get(size_t sampleCount, math::pimatrix& matRet);

    virtual void Append(std::vector<std::string>& files
                , size_t size, size_t dimension
                , model::DatasetInfo_DataFormat dataFormat);
        
    size_t GetDimension()
    {
        return m_iDimension;
    }
    
    /*
     * The number of samples in this set
     */
    size_t GetSize()
    {
        return m_dataSize;
    }
        
protected:
    
    virtual void loadFile(std::string sFile, math::pimatrix& matRet
                        , model::DatasetInfo_DataFormat dataFormat);
    
};

}
#endif      /* DISK_H */