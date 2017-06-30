#ifndef expree_ValueKind_HPP_INCLUDED
#define expree_ValueKind_HPP_INCLUDED




enum class
ValueKind
{
  null,
  undefined,
  integer,
  boolean,
  enumerator,
  pointer,
  reference,
  string,
  array,
  object,

};


struct
Undefined
{
  constexpr Undefined(){}
};


struct
Boolean
{
  bool  data;

  constexpr Boolean(bool  b=false): data(b){}

  constexpr Boolean  operator&&(const Boolean&  rhs) const{return Boolean(data&&rhs.data);}
  constexpr Boolean  operator||(const Boolean&  rhs) const{return Boolean(data||rhs.data);}
  constexpr Boolean  operator!() const{return Boolean(!data);}

};


#endif




