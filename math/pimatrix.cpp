/* 
 * File:   pimatrix.cpp
 * Author: hoaivu_pham
 * 
 * Created on September 9, 2013, 3:17 PM
 */

#include "pimatrix.h"

#include <boost/assert.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/random/variate_generator.hpp>
#include <sstream>
#include <iostream>
#include <fstream>

namespace bu = boost::numeric::ublas;

typedef boost::uniform_int<> distribution_type;
typedef boost::variate_generator<boost::minstd_rand&, distribution_type> gen_type;
    
namespace math
{

pimatrix::pimatrix()
: m_matrix(1, 1)
{   }

pimatrix::pimatrix(size_t m, size_t n)
: m_matrix (m, n)
{   }

pimatrix::pimatrix(const std::string& str)
{
    std::stringstream ss(str);
    bu::matrix<float> tmp;

    ss.seekg(0);
    ss >> tmp;
    m_matrix = tmp;
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

/*****************************************************************/

void pimatrix::setValue(float v)
{
    m_matrix = bu::scalar_matrix<float>(
            m_matrix.size1(), m_matrix.size2(), v);
}

/*
 * Set all columns to the parameter
 */
void pimatrix::setColumns(pimatrix& col)
{
    BOOST_ASSERT_MSG(m_matrix.size1() == col.size1() && col.size2() == 1,
            "Invalid dimensions");

    for (unsigned int i = m_matrix.size2() - 1; i >= 0; --i)
    {
        bu::column(m_matrix, i) = bu::column(col.m_matrix, 0);
    }
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

void pimatrix::mult(pimatrix& m)
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
        m_matrix = bu::block_prod<bu::matrix<float>, 64>(m_matrix, m.m_matrix);
    }
}

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
    boost::numeric::ublas::matrix<float> tmp;
    in >> tmp;
    m.m_matrix = tmp;
    return in;
}

void pimatrix::save(std::string sFileName)
{
    std::ofstream ofs(sFileName.c_str());
    boost::archive::binary_oarchive oa(ofs);
    
    oa << m_matrix;
}

void pimatrix::load(std::string sFileName)
{
    std::ifstream ifs(sFileName.c_str());
    boost::archive::binary_iarchive ia(ifs);
    ia >> m_matrix;
}
    
std::string pimatrix::ToString()
{
    std::stringstream ss;
    ss << m_matrix;
    return ss.str();
}

}