#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& msg);
template<typename T>
istream& operator>> (istream& is, vector<T>& msg);

#endif