#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct cartesion_vector{
  cartesion_vector() {}
  cartesion_vector(std::vector<float> in)
        : data(in) {}
        
    std::vector<float> data;
};

ostream& operator<<(ostream& os, const cartesion_vector& msg);
istream& operator>> (istream& is, cartesion_vector& msg);

#endif