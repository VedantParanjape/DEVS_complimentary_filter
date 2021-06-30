#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

istream& operator>> (istream& is, vector<float>& msg);
ostream& operator<<(ostream& os, const vector<float>& msg);

#endif