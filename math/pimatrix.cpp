/* 
 * File:   pimatrix.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 9, 2013, 3:17 PM
 */

#include <boost/assert.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "pimatrix.h"
#include "deeplearn.pb.h"
#include "Util.h"

namespace bu = boost::numeric::ublas;

typedef boost::uniform_int<> distribution_type;
typedef boost::variate_generator<boost::minstd_rand&, distribution_type> gen_type;

#define PIMATRIX_TINY (float)1E-10
#define PIMATRIX_HUGE (float)1E+10

#define INT_SIZE 4
#define HEADER_SIZE 12

namespace math
{

pimatrix::pimatrix()
: m_matrix(0, 0)
{   }

pimatrix::pimatrix(size_t m, size_t n, float initVal /*= 0*/)
: m_matrix (m, n, initVal)
{
}

pimatrix& pimatrix::operator=(const pimatrix &rhs)
{
    if (this != &rhs)
        m_matrix = rhs.m_matrix;
    return *this;
}

pimatrix& pimatrix::operator+=(const pimatrix &rhs)
{
    m_matrix += rhs.m_matrix;
    return *this;
}

pimatrix::~pimatrix()
{   }

float pimatrix::HugeValue()
{
    return PIMATRIX_HUGE;
}
/*****************************************************************/

void pimatrix::setValue(float v)
{
    m_matrix = bu::scalar_matrix<float>(
            m_matrix.size1(), m_matrix.size2(), v);
}

/*
 * Set all columns to the parameter
 */
void pimatrix::setValue(float v, size_t startRow, size_t rowCount
                    , size_t startCol, size_t colCount)
{
    BOOST_ASSERT_MSG(m_matrix.size1() >= startRow + rowCount
                  && m_matrix.size2() >= startCol + colCount,
            "There are fewer columns/rows than required.");

    bu::matrix<float> mTmp = bu::scalar_matrix<float>(rowCount, colCount, v);
    bu::project(m_matrix
            , bu::range(startRow, startRow + rowCount)
            , bu::range(startCol, startCol + colCount)) = mTmp;
}

void pimatrix::copyRows(pimatrix& source, size_t startRowSrc
            , size_t rowCount, size_t startRowDest)
{
    BOOST_ASSERT_MSG(source.size2() == size2() 
            && size1() >= startRowDest + rowCount
            && source.size1() >= startRowSrc + rowCount
            , "Invalid dimensions of the destination matrix");
    
    if (rowCount == 0)
        return;
    
    bu::project(m_matrix
            , bu::range(startRowDest, startRowDest + rowCount)
            , bu::range(0, source.size2())) = 
            bu::project(source.m_matrix
            , bu::range(startRowSrc, startRowSrc + rowCount)
            , bu::range(0, source.size2()));
}

/*
void pimatrix::copyRows(pimatrix& source, size_t startRow, size_t rowCount)
{
    BOOST_ASSERT_MSG(source.size2() == size2() && size1() == rowCount, "Invalid dimensions");
    m_matrix = bu::project(source.m_matrix, bu::range(startRow, startRow+rowCount)
            , bu::range(0, source.size2()));
}
*/

pimatrix pimatrix::rows(size_t startRow, size_t rowCount)
{
    BOOST_ASSERT(size1() > startRow && size1() >= startRow + rowCount
                    && rowCount > 0);
    pimatrix mRet(0,0);
    mRet.m_matrix = bu::project(m_matrix, bu::range(startRow, startRow+rowCount)
            , bu::range(0, size2()));
    return mRet;
}

void pimatrix::copyColumns(pimatrix& source, size_t startCol, size_t colCount)
{
    BOOST_ASSERT_MSG(source.size1() == size1() && size2() == colCount, "Invalid dimensions");
    m_matrix = bu::project(source.m_matrix, bu::range(0, source.size1())
        , bu::range(startCol, startCol + colCount));
}

void pimatrix::dot(pimatrix& m)
{
    m_matrix = bu::element_prod(m_matrix, m.m_matrix);
}

void pimatrix::mult(pimatrix& m, int transpose /*= 0*/)
{
    if (m.size1() == 1 && m.size2() == 1)
    {
        m_matrix *= m(0, 0);
    }
    else if (size1() == 1 && size2() == 1)
    {
        m_matrix = m_matrix(0, 0) * m.m_matrix;
    }
    else
    {
        switch(transpose)
        {
            case 1:
                // transpose this
                m_matrix = bu::block_prod<bu::matrix<float>, 64>
                        (bu::trans(m_matrix), m.m_matrix);
                break;
            case 2:
                // transpose this
                m_matrix = bu::block_prod<bu::matrix<float>, 64>
                        (m_matrix, bu::trans(m.m_matrix));
                break;
            case 0:
                m_matrix = bu::block_prod<bu::matrix<float>, 64>
                        (m_matrix, m.m_matrix);
                break;
            default:
                BOOST_ASSERT_MSG(false, "Wrong transpose mode. Can only be 0, 1, 2");
        }
    }
}

/*
pimatrix pimatrix::mult(pimatrix& m1, pimatrix& m2)
{
    pimatrix mRet;

    if (m2.size1() == 1 && m2.size2() == 1)
    {
        mRet.m_matrix = m2(0, 0) * m1.m_matrix;
    }
    else if (m1.size1() == 1 && m1.size2() == 1)
    {
        mRet.m_matrix = m1(0, 0) * m2.m_matrix;
    }
    else
    {
        mRet.m_matrix = bu::block_prod<bu::matrix<float>, 64>(m1.m_matrix, m2.m_matrix);
    }
    return mRet;
}
*/
/*
void pimatrix::mult_add(pimatrix& m1, pimatrix& m2)
{
    if (m2.size1() == 1 && m2.size2() == 1)
    {
        m_matrix += m2(0, 0) * m1.m_matrix;
        return;
    }
    if (m1.size1() == 1 && m1.size2() == 1)
    {
        m_matrix += m1(0, 0) * m2.m_matrix;
        return;
    }
    m_matrix += bu::block_prod<bu::matrix<float>, 64>(m1.m_matrix, m2.m_matrix);
}
*/

void pimatrix::sum(int dim, pimatrix& result)
{
    switch(dim)
    {
        case 0:
            result.resize(1, 1);
            result.set(0, 0, std::accumulate(
                m_matrix.data().begin(), m_matrix.data().end(), 0.0f));
            break;
        case 1:
        {
            if (size2() == 1)
            {
                result.resize(1, 1);
                result.set(0, 0, std::accumulate(
                    m_matrix.data().begin(), m_matrix.data().end(), 0.0f));
            }
            else
            {
                bu::matrix<float> identityRow(1, size1(), 1);
                result.m_matrix = bu::block_prod<bu::matrix<float>, 64>(identityRow, m_matrix);
            }
            break;
        }
        case 2:
        {
            bu::matrix<float> identityCol(size2(), 1, 1);
            result.m_matrix = bu::block_prod<bu::matrix<float>, 64>(m_matrix, identityCol);
            break;
        }
        default:
            BOOST_ASSERT_MSG(false, "Invalid argument (dim)");
    }
}

/******************************************************************************/

float op_inverse(float x){return 1.0f/(x + PIMATRIX_TINY);}
float op_add_tiny(float x)
{
    return (x < -PIMATRIX_TINY || x > PIMATRIX_TINY ? x :
        (x < PIMATRIX_TINY && x >= 0 ? PIMATRIX_TINY : -PIMATRIX_TINY));
}
float op_neg_log(float x)
{
    return (x <= PIMATRIX_TINY ? PIMATRIX_HUGE : -std::log(x));
}
float op_log(float x)
{
    return (x <= PIMATRIX_TINY ? -PIMATRIX_HUGE : std::log(x));
}

void pimatrix::element_inverse()
{
    std::transform(m_matrix.data().begin(), m_matrix.data().end(),
               m_matrix.data().begin(), op_inverse);
}

void pimatrix::element_mult(const pimatrix& m)
{
    m_matrix = bu::element_prod(m_matrix, m.m_matrix);
}
    
void pimatrix::element_div(const pimatrix& m)
{
    bu::matrix<float> tmp = m.m_matrix;
    std::transform(tmp.data().begin(), tmp.data().end(),
               tmp.data().begin(), op_add_tiny);
    m_matrix = bu::element_div(m_matrix, tmp);
}

void pimatrix::element_add(pimatrix& m, float beta)
{
    m_matrix += beta * m.m_matrix;
}

void pimatrix::element_negate(size_t startRow, size_t rowCount
                        , size_t startCol, size_t colCount)
{
    bu::project(m_matrix
        , bu::range(startRow, startRow + rowCount)
        , bu::range(startCol, startCol + colCount)) = 
    (-1)*bu::project(m_matrix
        , bu::range(startRow, startRow + rowCount)
        , bu::range(startCol, startCol + colCount));
}

void pimatrix::element_log(bool bNegativeLog /*= false*/)
{
    std::transform(m_matrix.data().begin(), m_matrix.data().end(),
               m_matrix.data().begin(), bNegativeLog ? op_neg_log : op_log);
}

/******************************************************************************/

void pimatrix::shuffleRows(boost::minstd_rand& generator)
{
    for(size_t r = m_matrix.size1() - 1; r > 0; --r)
    {
        gen_type rnd(generator, distribution_type(0, r-1));
        size_t t = rnd();
        BOOST_ASSERT(0 <= t && t < r);
        
        bu::matrix<float> m(1, m_matrix.size2());
        bu::row(m, 0) = bu::row(m_matrix, r);
        bu::row(m_matrix, r) = bu::row(m_matrix, t);
        bu::row(m_matrix, t) = bu::row(m, 0);
    }
}

/*****************************************************************/

size_t pimatrix::size1() const
{
    return m_matrix.size1();
}

size_t pimatrix::size2() const
{
    return m_matrix.size2();
}

void pimatrix::resize(size_t size1, size_t size2, bool preserve /*= false*/)
{
    if (m_matrix.size1() != size1 || m_matrix.size2() != size2)
        m_matrix.resize(size1, size2, preserve);
}

boost::numeric::ublas::matrix<float>::const_reference 
pimatrix::operator () (size_t i, size_t j) const
{
    return m_matrix(i, j);
}

void pimatrix::set(size_t i, size_t j, float val)
{
    m_matrix(i, j) = val;
}

std::ostream& operator<< (std::ostream &out, pimatrix &m)
{
    out << m.m_matrix;
    return out;
}

std::istream& operator>> (std::istream &in, pimatrix &m)
{
    in >> m.m_matrix;
    return in;
}

void pimatrix::save(std::string sFileName)
{
    char *bytes;
    size_t sz;

    std::ofstream ofs(sFileName.c_str()
        , std::ios_base::out | std::ios_base::binary);

    ofs.seekp(0);
    sz = ToArray(bytes);
    ofs.write(bytes, sz);
    ofs.flush();
    ofs.close();
    delete[] bytes;
}

bool pimatrix::load(std::string sFileName)
{
    std::ifstream ifs(sFileName.c_str()
        , std::ios_base::in | std::ios_base::binary);
    ifs.seekg(0);
    bool bRet = FromStream(ifs);
    ifs.close();
    return bRet;
}

template<class T>
T op_string2number(std::string x)
{
    std::stringstream ss(x);
    T f;
    ss >> f;
    return f;
}
bool pimatrix::loadCsv(const std::string& sCsvFilePath)
{
    std::ifstream f(sCsvFilePath.c_str(), std::ios_base::in);
    size_t sz1, sz2;
    std::string sLine;
    std::vector<std::string> vLine;
    std::vector<std::vector<float> > arrFile;
    std::vector<float> arrLine;
    
    sz1 = sz2 = 0;
    while (std::getline(f, sLine))
    {
        if(sLine.length() == 0)
            continue;
        
        ++sz1;
        vLine.clear();
        boost::split(vLine, sLine, boost::is_any_of(","));
        if (sz2 == 0)
        {
            sz2 = vLine.size();
        }
        else if (sz2 != vLine.size())
        {
            std::cout << "Invalid CSV file: " << sCsvFilePath
                      << " at line " << sz1 << std::endl;
            f.close();
            return false;
        }
        arrLine.resize(sz2, 0);
        std::transform(vLine.begin(), vLine.end()
            , arrLine.begin(), op_string2number<float>);
        arrFile.push_back(arrLine);
    }
    f.close();
    
    m_matrix.resize(sz1, sz2);
    for (size_t i = 0; i < sz1; ++i)
    {
        const std::vector<float> aLine = arrFile.at(i);
        for(size_t j = 0; j < sz2; ++j)
        {
            m_matrix(i, j) = aLine.at(j);
        }
    }
    
    return true;
}

/*************************************************************************/

std::string pimatrix::ToString()
{
    char *bytes;
    size_t sz;

    sz = ToArray(bytes);
    std::string sRet(bytes, sz);
    delete[] bytes;
    return sRet;
}

bool pimatrix::FromString(const std::string& sMat)
{
    char *bytes = (char*)sMat.data();
    size_t sz, sz1, sz2;

    if (sMat.size() < HEADER_SIZE)
        return false;

    sz = util::Util::ReadSize(bytes);
    sz1 = util::Util::ReadSize(bytes + INT_SIZE);
    sz2 = util::Util::ReadSize(bytes + 2*INT_SIZE);

    sz -= HEADER_SIZE;
    if(sz != sMat.size() - HEADER_SIZE || sz != sz1 * sz2 * INT_SIZE)
        return false;

    m_matrix.resize(sz1, sz2);
    bytes += HEADER_SIZE;
    for (size_t i = 0; i < sz1; ++i)
    {
        for (size_t j = 0; j < sz2; ++j)
        {
            m_matrix(i, j) = util::Util::ReadFloat(bytes);
            bytes += INT_SIZE;
        }
    }
    return true;
}

std::string pimatrix::ToDebugString()
{
    std::stringstream ss;
    ss << m_matrix;
    return ss.str();
}

void pimatrix::FromDebugString(const std::string& sMat)
{
    std::stringstream ss(sMat);
    ss.seekg(0);
    ss >> m_matrix;
}
/****************************************************************************/

size_t pimatrix::ToArray(char* &bytes)
{
    BOOST_ASSERT_MSG(sizeof(float) == INT_SIZE,
        "Unportable with this platform.");

    size_t sz = size1()*size2()*INT_SIZE + HEADER_SIZE;
    bytes = new char[sz];
    util::Util::WriteSize(sz, bytes);
    util::Util::WriteSize(size1(), bytes + INT_SIZE);
    util::Util::WriteSize(size2(), bytes + 2*INT_SIZE);
    char *arr = bytes + 3*INT_SIZE;

    for (size_t i = 0; i < size1(); ++i)
    {
        for (size_t j = 0; j < size2(); ++j)
        {
            util::Util::WriteFloat(m_matrix(i, j), arr);
            arr += INT_SIZE;
        }
    }
    return sz;
}

bool pimatrix::FromStream(std::istream& stream)
{
    char header[HEADER_SIZE], *matrixData;
    stream.read(header, HEADER_SIZE);

    size_t sz = util::Util::ReadSize(header);
    size_t sz1 = util::Util::ReadSize(header + INT_SIZE);
    size_t sz2 = util::Util::ReadSize(header + 2*INT_SIZE);
    
    if (sz <= HEADER_SIZE)
        return false;

    sz -= HEADER_SIZE;
    if(sz != sz1 * sz2 * INT_SIZE)
        return false;

    matrixData = new char[sz];
    size_t readCount = 0;
    while(readCount < sz)
    {
        stream.read(matrixData + readCount, sz-readCount);
        readCount += stream.gcount();
        if (stream.gcount() == 0)
            break;
    }

    if (readCount == sz)
    {
        m_matrix.resize(sz1, sz2);
        char *arr = matrixData;
        for (size_t i = 0; i < sz1; ++i)
        {
            for (size_t j = 0; j < sz2; ++j)
            {
                m_matrix(i, j) = util::Util::ReadFloat(arr);
                arr += INT_SIZE;
            }
        }
    }
    
    delete[] matrixData;
    return (readCount == sz);
}
    
}