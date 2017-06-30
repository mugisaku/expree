#ifndef expree_Boolean_HPP_INCLUDED
#define expree_Boolean_HPP_INCLUDED


#include"expree_ValueKind.hpp"


struct
Boolean
{
  int  data;

  constexpr Boolean(int  d=0): data(d){}


  Boolean  operator||(const Boolean&  rhs) const{return Boolean(data||rhs.data);}
  Boolean  operator&&(const Boolean&  rhs) const{return Boolean(data&&rhs.data);}

};


#endif




