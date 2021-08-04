#include "message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const cartesian_vector& msg) {
  os << " x: " << msg.data[0] << " y: " << msg.data[1] << " z: " << msg.data[2];
  
  return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

istream& operator>> (istream& is, cartesian_vector& msg) { 
  is >> msg.data[0] >> msg.data[1] >> msg.data[2];

  return is;
}