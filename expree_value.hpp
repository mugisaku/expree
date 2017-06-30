#ifndef expree_Value_HPP_INCLUDED
#define expree_Value_HPP_INCLUDED


#include"expree_ValueKind.hpp"
#include"expree_integer.hpp"
#include"expree_reference.hpp"
#include<cstdarg>
#include<string>
#include<utility>
#include<new>
#include<exception>


union
ValueData
{
  Integer      integer;
  Boolean      boolean;
  Reference  reference;

   ValueData(){}
  ~ValueData(){}

};


class
ValueException: public std::exception
{
  char  buf[256];

public:
  ValueException(const char*  fmt, ...)
  {
    va_list  ap;

    va_start(ap,fmt);

    vsnprintf(buf,sizeof(buf),fmt,ap);

    va_end(ap);
  }

  const char*  what() const noexcept override{return buf;}

};



class
Value
{
  ValueKind  kind;
  ValueData  data;

public:
  Value(                  ): kind(ValueKind::null){}
  Value(Undefined&&  undef): kind(ValueKind::undefined){}
  Value(Integer&&        i): kind(ValueKind::integer){new(&data) Integer(std::move(i));}
  Value(Boolean&&        b): kind(ValueKind::boolean){new(&data) Boolean(std::move(b));}
  Value(Reference&&      r): kind(ValueKind::reference){new(&data) Reference(std::move(r));}


  const ValueData*  operator->() const{return &data;}

  bool  operator==(ValueKind  k) const{return kind == k;}

  Value  operator +(const Value&  rhs) const;
  Value  operator -(const Value&  rhs) const;
  Value  operator *(const Value&  rhs) const;
  Value  operator /(const Value&  rhs) const;
  Value  operator %(const Value&  rhs) const;

  Value  operator<<(const Value&  rhs) const;
  Value  operator>>(const Value&  rhs) const;
  Value  operator |(const Value&  rhs) const;
  Value  operator &(const Value&  rhs) const;
  Value  operator ^(const Value&  rhs) const;
  Value  operator~() const;

  Value  operator==(const Value&  rhs) const;
  Value  operator!=(const Value&  rhs) const;
  Value  operator< (const Value&  rhs) const;
  Value  operator<=(const Value&  rhs) const;
  Value  operator> (const Value&  rhs) const;
  Value  operator>=(const Value&  rhs) const;

  Value  operator||(const Value&  rhs) const;
  Value  operator&&(const Value&  rhs) const;
  Value  operator!() const;

  Value  operator =(const Value&  rhs) const;
  Value  operator+=(const Value&  rhs) const;
  Value  operator-=(const Value&  rhs) const;
  Value  operator*=(const Value&  rhs) const;
  Value  operator/=(const Value&  rhs) const;
  Value  operator%=(const Value&  rhs) const;
  Value  operator<<=(const Value&  rhs) const;
  Value  operator>>=(const Value&  rhs) const;
  Value  operator&=(const Value&  rhs) const;
  Value  operator|=(const Value&  rhs) const;
  Value  operator^=(const Value&  rhs) const;

  Value  operator*() const;
  Value  operator-() const;

  Integer  to_integer() const;
  Boolean  to_boolean() const;
  Reference  to_reference() const;

  ValueKind   get_kind() const{return kind;}

};


#endif




