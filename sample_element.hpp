#ifndef SAMPLE_ELEMENT_HPP_INCLUDED
#define SAMPLE_ELEMENT_HPP_INCLUDED


#include"expree.hpp"
#include"sample_operand.hpp"
#include<cstdint>


using namespace expree;


struct
Operator
{
  char  codes[4];


constexpr Operator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
codes{c0,c1,c2,c3}
{}


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
Operator(c0,c1,c2,c3)
{}
};


struct
BinaryOperator: Operator
{
constexpr BinaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
Operator(c0,c1,c2,c3)
{}
};


struct
Element
{
  ElementKind  kind;

  union Data{
   Operator  operator_;

   Operand  operand;

   Data(                        ): operand(0){}
   Data(Operand&&              o): operand(std::move(o)){}
   Data(const UnaryOperator&   o): operator_(o){}
   Data(const BinaryOperator&  o): operator_(o){}
   ~Data(){}

  } data;


  Element();
  Element(Operand&&  o);
  Element(const UnaryOperator&  o);
  Element(const BinaryOperator&  o);
  Element(const Element&  rhs);
  Element(Element&&  rhs) noexcept;
  ~Element();


  Element&  operator=(const Element&   rhs)         ;
  Element&  operator=(      Element&&  rhs) noexcept;

  operator   ElementKind() const;
  operator Associativity() const;
  operator    Precedence() const;

  void  clear();

  void  print(bool  parenthesis=false) const;

};


#endif




