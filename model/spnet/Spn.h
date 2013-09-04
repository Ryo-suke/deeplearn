/* 
 * File:   spn.h
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 5:34 PM
 */

#ifndef SPN_H
#define	SPN_H

#include <Model.h>

namespace model
{

class Spn : public Model
{
public:
    Spn();
    Spn(const Spn& orig);
    virtual ~Spn();
    
    math::pimatrix Forward(){}
    void Backward(){}
    void Train(){}
    
private:

};

}

#endif	/* SPN_H */

