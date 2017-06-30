#include"expree_reference.hpp"
#include"expree_value.hpp"




Value  Reference::operator  =(const Value&  rhs) const{return target =        rhs;}
Value  Reference::operator +=(const Value&  rhs) const{return target = target+rhs;}
Value  Reference::operator -=(const Value&  rhs) const{return target = target-rhs;}
Value  Reference::operator *=(const Value&  rhs) const{return target = target*rhs;}
Value  Reference::operator /=(const Value&  rhs) const{return target = target/rhs;}
Value  Reference::operator %=(const Value&  rhs) const{return target = target%rhs;}
Value  Reference::operator<<=(const Value&  rhs) const{return target = target<<rhs;}
Value  Reference::operator>>=(const Value&  rhs) const{return target = target>>rhs;}
Value  Reference::operator |=(const Value&  rhs) const{return target = target|rhs;}
Value  Reference::operator &=(const Value&  rhs) const{return target = target&rhs;}
Value  Reference::operator ^=(const Value&  rhs) const{return target = target^rhs;}


Value&
Reference::
get_value() const
{
  return target;
}




