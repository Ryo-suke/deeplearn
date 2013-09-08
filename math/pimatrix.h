/* 
 * File:   pimatrix.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 3:34 PM
 */

#ifndef PIMATRIX_H
#define	PIMATRIX_H

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>
#include <boost/assert.hpp>
#include <iostream>
#include <string>
#include <sstream>

namespace bu = boost::numeric::ublas;

namespace math
{

/*
 * Platform-independent vector
 */
class pimatrix
{
    bu::matrix<float> m_matrix;
    
public:
    
    pimatrix()
    : m_matrix(1, 1)
    {   }
    
    pimatrix(size_t m, size_t n)
    : m_matrix (m, n)
    {   }
    
    pimatrix(const std::string& str)
    {
        std::stringstream ss(str);
        bu::matrix<float> tmp;
        
        ss.seekg(0);
        ss >> tmp;
        m_matrix = tmp;
    }
    
    pimatrix& operator=(const pimatrix &rhs)
    {
        m_matrix = rhs.m_matrix;
        return *this;
    }

    pimatrix& operator+=(const pimatrix &rhs)
    {
        m_matrix += rhs.m_matrix;
        return *this;
    }

    virtual ~pimatrix()
    {   }
    
    /*****************************************************************/
    
    void setValue(float v)
    {
        m_matrix = bu::scalar_matrix<float>(
                m_matrix.size1(), m_matrix.size2(), v);
    }
    
    /*
     * Set all columns to the parameter
     */
    void setColumns(pimatrix& col)
    {
        BOOST_ASSERT_MSG(m_matrix.size1() == col.size1() && col.size2() == 1,
                "Invalid dimensions");
        
        for (unsigned int i = m_matrix.size2() - 1; i >= 0; --i)
        {
            bu::column(m_matrix, i) = bu::column(col.m_matrix, 0);
        }
    }
    
    void copyRows(pimatrix& source, size_t startRow, size_t rowCount)
    {
        BOOST_ASSERT_MSG(source.size2() == size2() && size1() == rowCount, "Invalid dimensions");
        m_matrix = bu::project(source.m_matrix, bu::range(startRow, startRow+rowCount)
                , bu::range(0, source.size2()));
    }
    
    void copyColumns(pimatrix& source, size_t startCol, size_t colCount)
    {
        BOOST_ASSERT_MSG(source.size1() == size1() && size2() == colCount, "Invalid dimensions");
        m_matrix = bu::project(source.m_matrix, bu::range(0, source.size1())
            , bu::range(startCol, startCol + colCount));
    }

    void assign(pimatrix& m)
    {
        m_matrix = m.m_matrix;
    }

    void dot(pimatrix& m)
    {
        m_matrix = bu::element_prod(m_matrix, m.m_matrix);
    }

    void mult(pimatrix& m)
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

    static pimatrix mult(pimatrix& m1, pimatrix& m2)
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

    void mult_add(pimatrix& m1, pimatrix& m2)
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
    /*****************************************************************/
    
    size_t size1() const
    {
        return m_matrix.size1();
    }
    
    size_t size2() const
    {
        return m_matrix.size2();
    }

    void resize(size_t size1, size_t size2, bool preserve = false)
    {
        m_matrix.resize(size1, size2, preserve);
    }
    
    boost::numeric::ublas::matrix<float>::const_reference 
    operator () (size_t i, size_t j) const
    {
        return m_matrix(i, j);
    }
    
    void set(size_t i, size_t j, float val)
    {
        m_matrix(i, j) = val;
    }
        
    friend std::ostream& operator<< (std::ostream &out, pimatrix &m)
    {
        out << m.m_matrix;
        return out;
    }
    
    friend std::istream& operator>> (std::istream &in, pimatrix &m)
    {
        boost::numeric::ublas::matrix<float> tmp;
        in >> tmp;
        m.m_matrix = tmp;
        return in;
    }
    
    std::string ToString()
    {
        std::stringstream ss;
        ss << m_matrix;
        return ss.str();
    }

    /*************************************************************************/
};

}


#endif	/* PIMATRIX_H */

