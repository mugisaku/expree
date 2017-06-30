#ifndef expree_Operator_HPP_INCLUDED
#define expree_Operator_HPP_INCLUDED


#include<cstdint>


struct
Operator
{
  char  codes[4];


  constexpr Operator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
  codes{c0,c1,c2,c3}{}


  constexpr operator uint32_t() const
  {
    return((codes[0]<<24)|
           (codes[1]<<16)|
           (codes[2]<< 8)|
           (codes[3]    ));
  }

};


struct
UnaryOperator: Operator
{
  constexpr UnaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
  Operator(c0,c1,c2,c3){}

};


struct
BinaryOperator: Operator
{
  constexpr BinaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
  Operator(c0,c1,c2,c3){}

};


#endif




