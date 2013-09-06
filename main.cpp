/* 
 * File:   main.cpp
 * Author: hoaivu_pham
 *
 * Created on September 4, 2013, 2:39 PM
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <pimatrix.h>

#include "deeplearn.pb.h"
#include <spnet/Spn.h>


void testMatrix()
{
    math::pimatrix m(3, 3);
    std::cout << m;
    
    std::cin >> m;
    m.set(0, 0, -100);
    std::cout << m;
}

void testNodeData()
{
    model::NodeData d = model::NodeData::default_instance();
    model::NodeData d2 = d;
    d.set_name("Node d");
    d2.set_name("Node d2");
    std::cout << d.SerializeAsString() << std::endl << d2.SerializeAsString()
            << std::endl << model::NodeData::default_instance().SerializeAsString();
}

/*
 * 
 */
int main(int argc, char** argv) 
{
    //testMatrix();
    testNodeData();
    return 0;
}

