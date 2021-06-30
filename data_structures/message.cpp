#include "message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const vector<float>& msg) {
  os << " x: " << msg[0] << " y: " << msg[1] << " z: " << msg[2] << "\n";
  return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

istream& operator>> (istream& is, vector<float>& msg) {
  is >> msg[0] >> msg[1] >> msg[2];
  return is;
}