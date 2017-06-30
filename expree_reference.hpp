#ifndef expree_Reference_HPP_INCLUDED
#define expree_Reference_HPP_INCLUDED


#include"expree_ValueKind.hpp"


struct Value;


struct
Reference
{
  Value&  target;

  Reference(Value&  target_): target(target_){}

  Value  operator  =(const Value&  rhs) const;
  Value  operator +=(const Value&  rhs) const;
  Value  operator -=(const Value&  rhs) const;
  Value  operator *=(const Value&  rhs) const;
  Value  operator /=(const Value&  rhs) const;
  Value  operator %=(const Value&  rhs) const;
  Value  operator<<=(const Value&  rhs) const;
  Value  operator>>=(const Value&  rhs) const;
  Value  operator |=(const Value&  rhs) const;
  Value  operator &=(const Value&  rhs) const;
  Value  operator ^=(const Value&  rhs) const;

  Value&  get_value() const;

};


#endif




