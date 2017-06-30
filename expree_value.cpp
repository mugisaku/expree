#include"expree_value.hpp"




Value  Value::operator =(const Value&  rhs) const{return to_reference() = rhs;}
Value  Value::operator+=(const Value&  rhs) const{return to_reference() += rhs;}
Value  Value::operator-=(const Value&  rhs) const{return to_reference() -= rhs;}
Value  Value::operator*=(const Value&  rhs) const{return to_reference() *= rhs;}
Value  Value::operator/=(const Value&  rhs) const{return to_reference() /= rhs;}
Value  Value::operator%=(const Value&  rhs) const{return to_reference() %= rhs;}
Value  Value::operator<<=(const Value&  rhs) const{return to_reference() <<= rhs;}
Value  Value::operator>>=(const Value&  rhs) const{return to_reference() >>= rhs;}
Value  Value::operator&=(const Value&  rhs) const{return to_reference() &= rhs;}
Value  Value::operator|=(const Value&  rhs) const{return to_reference() |= rhs;}
Value  Value::operator^=(const Value&  rhs) const{return to_reference() ^= rhs;}


Value  Value::operator*() const{return Value(Boolean());}
Value  Value::operator-() const{return Value(-to_integer());}


Value  Value::operator +(const Value&  rhs) const{return Value(to_integer()+rhs.to_integer());}
Value  Value::operator -(const Value&  rhs) const{return Value(to_integer()-rhs.to_integer());}
Value  Value::operator *(const Value&  rhs) const{return Value(to_integer()*rhs.to_integer());}
Value  Value::operator /(const Value&  rhs) const{return Value(to_integer()/rhs.to_integer());}
Value  Value::operator %(const Value&  rhs) const{return Value(to_integer()%rhs.to_integer());}


Value  Value::operator<<(const Value&  rhs) const{return Value(to_integer()<<rhs.to_integer());}
Value  Value::operator>>(const Value&  rhs) const{return Value(to_integer()>>rhs.to_integer());}
Value  Value::operator |(const Value&  rhs) const{return Value(to_integer() |rhs.to_integer());}
Value  Value::operator &(const Value&  rhs) const{return Value(to_integer() &rhs.to_integer());}
Value  Value::operator ^(const Value&  rhs) const{return Value(to_integer() ^rhs.to_integer());}
Value  Value::operator ~() const{return Value(~to_integer());}


Value  Value::operator==(const Value&  rhs) const{return Value(to_integer() == rhs.to_integer());}
Value  Value::operator!=(const Value&  rhs) const{return Value(to_integer() != rhs.to_integer());}
Value  Value::operator< (const Value&  rhs) const{return Value(to_integer() <  rhs.to_integer());}
Value  Value::operator<=(const Value&  rhs) const{return Value(to_integer() <= rhs.to_integer());}
Value  Value::operator> (const Value&  rhs) const{return Value(to_integer() >  rhs.to_integer());}
Value  Value::operator>=(const Value&  rhs) const{return Value(to_integer() >= rhs.to_integer());}


Value  Value::operator!()                   const{return Value(!to_boolean());}
Value  Value::operator||(const Value&  rhs) const{return Value(to_boolean() || rhs.to_boolean());}
Value  Value::operator&&(const Value&  rhs) const{return Value(to_boolean() && rhs.to_boolean());}




Integer
Value::
to_integer() const
{
    switch(kind)
    {
  case(ValueKind::integer):
      return data.integer;
      break;
  case(ValueKind::boolean):
      break;
  case(ValueKind::reference):
      return data.reference.get_value().to_integer();
      break;
    }


  throw ValueException("整数に変換できません\n");
}


Boolean
Value::
to_boolean() const
{
    switch(kind)
    {
  case(ValueKind::integer):
      return Boolean(data.integer.data);
      break;
  case(ValueKind::boolean):
      return data.boolean;
      break;
  case(ValueKind::reference):
      return data.reference.get_value().to_boolean();
      break;
    }


  throw ValueException("真偽値に変換できません\n");
}


Reference
Value::
to_reference() const
{
    switch(kind)
    {
  case(ValueKind::integer):
      break;
  case(ValueKind::boolean):
      break;
  case(ValueKind::reference):
      return data.reference;
      break;
    }


  throw ValueException("参照ではありません\n");
}




