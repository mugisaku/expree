#ifndef expree_ELEMENT_HPP_INCLUDED
#define expree_ELEMENT_HPP_INCLUDED


#include"expree_operator.hpp"
#include"expree_operand.hpp"
#include"expree_element.hpp"
#include"expree_value.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


struct Scope;



enum class
ElementKind
{
  null,
  operand,
  operator_,
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

  Element*   left;
  Element*  right;

public:
  Element();
  Element(Operand&&  o);
  Element(const      Operator&  o);
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

  void  insert_to_left( Element*  e);
  void  insert_to_right(Element*  e);

  const Element*  get_left()  const{return  left;}
  const Element*  get_right() const{return right;}

  Value  make_value(Scope&  scope) const;

  void  print() const;

};




#endif




