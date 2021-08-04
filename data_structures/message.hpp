#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct cartesian_vector{
  cartesian_vector() {}
  cartesian_vector(std::vector<float> in)
        : data(in) {}
        
    std::vector<float> data;
};

ostream& operator<<(ostream& os, const cartesian_vector& msg);
istream& operator>> (istream& is, cartesian_vector& msg);

#endif