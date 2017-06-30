#ifndef expree_Integer_HPP_INCLUDED
#define expree_Integer_HPP_INCLUDED


#include"expree_ValueKind.hpp"


struct
Integer
{
  int  data;

  constexpr Integer(int  d=0): data(d){}


  Integer  operator +(const Integer&  rhs) const{return Integer(data+rhs.data);}
  Integer  operator -(const Integer&  rhs) const{return Integer(data-rhs.data);}
  Integer  operator *(const Integer&  rhs) const{return Integer(data*rhs.data);}
  Integer  operator /(const Integer&  rhs) const{return Integer(data/rhs.data);}
  Integer  operator %(const Integer&  rhs) const{return Integer(data%rhs.data);}
  Integer  operator<<(const Integer&  rhs) const{return Integer(data<<rhs.data);}
  Integer  operator>>(const Integer&  rhs) const{return Integer(data>>rhs.data);}
  Integer  operator==(const Integer&  rhs) const{return Integer(data == rhs.data);}
  Integer  operator!=(const Integer&  rhs) const{return Integer(data != rhs.data);}
  Integer  operator< (const Integer&  rhs) const{return Integer(data <  rhs.data);}
  Integer  operator<=(const Integer&  rhs) const{return Integer(data <= rhs.data);}
  Integer  operator> (const Integer&  rhs) const{return Integer(data >  rhs.data);}
  Integer  operator>=(const Integer&  rhs) const{return Integer(data >= rhs.data);}
  Integer  operator |(const Integer&  rhs) const{return Integer(data|rhs.data);}
  Integer  operator &(const Integer&  rhs) const{return Integer(data&rhs.data);}
  Integer  operator ^(const Integer&  rhs) const{return Integer(data^rhs.data);}

  Integer  operator~() const{return Integer(~data);}
  Integer  operator-() const{return Integer(-data);}

};


#endif




