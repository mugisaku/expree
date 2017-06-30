#ifndef expree_OPERAND_HPP_INCLUDED
#define expree_OPERAND_HPP_INCLUDED


#include<string>




enum class
OperandKind
{
  null,
  identifier,
  integer,
  element,

};


struct Element;


union
OperandData
{
  unsigned int  integer;

  std::string  identifier;

  Element*  element;

   OperandData(){}
  ~OperandData(){}

};


class
Operand
{
  OperandKind  kind;
  OperandData  data;

public:
  Operand();
  Operand(std::string&&  s);
  Operand(unsigned int   i);
  Operand(Element*       e);
  Operand(const Operand&   rhs) noexcept;
  Operand(      Operand&&  rhs) noexcept;
 ~Operand();


  Operand&  operator=(const Operand&   rhs) noexcept;
  Operand&  operator=(      Operand&&  rhs) noexcept;

  const OperandData*  operator->() const{return &data;}

  bool  operator==(OperandKind  k) const{return(kind == k);}
  bool  operator!=(OperandKind  k) const{return(kind != k);}

  OperandKind  get_kind() const{return kind;}

  void  clear();

  void  print() const;


};


#endif




