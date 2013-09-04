/* 
 * File:   pimatrix.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 3:34 PM
 */

#ifndef PIMATRIX_H
#define	PIMATRIX_H

#include <boost/numeric/ublas/matrix.hpp>

namespace math
{

/*
 * Platform-independent vector
 */
class pimatrix
{
public:
    
    pimatrix()
    {
        
    }
    
    pimatrix(int m, int n)
    {
        
    }
    
    pimatrix(const pimatrix& other)
    {
        
    }
    
    virtual ~pimatrix()
    {
        
    }
};

}


#endif	/* PIMATRIX_H */

