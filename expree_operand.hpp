#ifndef expree_OPERAND_HPP_INCLUDED
#define expree_OPERAND_HPP_INCLUDED


#include<string>
#include<vector>




enum class
OperandKind
{
  null,
  identifier,
  integer,
  element,

};


struct Element;
struct Operand;


union
OperandData
{
  unsigned int  integer;

  std::string  identifier;

  std::vector<Operand>  list;

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




