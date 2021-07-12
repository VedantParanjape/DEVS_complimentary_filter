#include "message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& msg) {
  os << " x: " << msg[0] << " y: " << msg[1] << " z: " << msg[2] << "\n";
  return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

template<typename T>
istream& operator>> (istream& is, vector<T>& msg) {
  is >> msg[0] >> msg[1] >> msg[2];
  return is;
}