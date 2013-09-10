/* 
 * File:   pimatrix.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 3:34 PM
 */

#ifndef PIMATRIX_H
#define	PIMATRIX_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <string>

namespace math
{

/*
 * Platform-independent vector
 */
class pimatrix
{
    boost::numeric::ublas::matrix<float> m_matrix;
    
public:
    
    pimatrix();
    
    pimatrix(size_t m, size_t n);
    
    pimatrix(const std::string& str);
    
    pimatrix& operator=(const pimatrix &rhs);

    pimatrix& operator+=(const pimatrix &rhs);
    
    virtual ~pimatrix();
    
    /*****************************************************************/
    
    void setValue(float v);
    
    /*
     * Set a slice of the matrix to the given value
     */
    void setValue(float v, size_t startCol, size_t colCount, size_t startRow, size_t rowCount);
    
    void copyRows(pimatrix& source, size_t startRowSrc
                , size_t rowCount, size_t startRowDest);
    
    //void copyRows(pimatrix& source, size_t startRow, size_t rowCount);
    
    pimatrix rows(size_t startRow, size_t rowCount);
    
    void copyColumns(pimatrix& source, size_t startCol, size_t colCount);

    void dot(pimatrix& m);

    /*
     * transpose = 0: no transpose before multiplying
     * transpose = 1: transpose this
     * transpose = 2: transpose m
     */
    void mult(pimatrix& m, int transpose = 0);

    //static pimatrix mult(pimatrix& m1, pimatrix& m2);

    void mult_add(pimatrix& m1, pimatrix& m2);
    
    /*****************************************************************/
    
    /*
     * Compute 1/x for each entry x in the matrix
     */
    void element_inverse();

    void element_mult(pimatrix& m);
    
    void element_div(pimatrix& m);
    
    /*
     * this += beta * m
     */
    void element_add(pimatrix& m, float beta = 1);
    
    /*****************************************************************/
    
    void shuffleRows(boost::minstd_rand& generator);
    
    /*****************************************************************/
    
    size_t size1() const;
    
    size_t size2() const;

    void resize(size_t size1, size_t size2, bool preserve = false);
    
    boost::numeric::ublas::matrix<float>::const_reference 
    operator () (size_t i, size_t j) const;
    
    void set(size_t i, size_t j, float val);
        
    friend std::ostream& operator<< (std::ostream &out, pimatrix &m);
    
    friend std::istream& operator>> (std::istream &in, pimatrix &m);
    
    //friend bool operator==(const pimatrix& lhs, const pimatrix& rhs);
    
    void save(std::string sFileName);
    
    void load(std::string sFileName);
    
    std::string ToString();

    /*************************************************************************/
};

}


#endif	/* PIMATRIX_H */

