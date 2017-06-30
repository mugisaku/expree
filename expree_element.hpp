#ifndef expree_ELEMENT_HPP_INCLUDED
#define expree_ELEMENT_HPP_INCLUDED


#include"expree_operator.hpp"
#include"expree_operand.hpp"




enum class
ElementKind
{
  null,
  operand,
  unary_operator,
  binary_operator,

};


union
ElementData
{
  Operator  operator_;
  Operand   operand;

   ElementData(){}
  ~ElementData(){}

};


class
Element
{
  ElementKind  kind;
  ElementData  data;

public:
  Element();
  Element(Operand&&  o);
  Element(const UnaryOperator&  o);
  Element(const BinaryOperator&  o);
  Element(const Element&   rhs) noexcept;
  Element(      Element&&  rhs) noexcept;
  ~Element();


  Element&  operator=(const Element&   rhs) noexcept;
  Element&  operator=(      Element&&  rhs) noexcept;

  const ElementData*  operator->() const{return &data;}

  bool  operator==(ElementKind  k) const{return(kind == k);}
  bool  operator!=(ElementKind  k) const{return(kind != k);}

  ElementKind  get_kind() const{return kind;}

  void  clear();

  void  print(bool  parenthesis=false) const;

};




#endif




