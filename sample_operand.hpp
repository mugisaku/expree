#ifndef SAMPLE_OPERAND_HPP_INCLUDED
#define SAMPLE_OPERAND_HPP_INCLUDED


#include"sample_object.hpp"




struct
Value
{
  int  integer;

  Object*  object;

  Value(int      i=0): object(nullptr), integer(i         ){}
  Value(Object*  o  ): object(o      ), integer(o->integer){}

  int&  operator*(){return object? object->integer:integer;}

};


enum class
OperandKind
{
  null,
  identifier,
  integer,
  node,

};


namespace expree{
template<typename  E> struct Node;
}


struct Element;


struct
Operand
{
  using Node = expree::Node<Element>;

  OperandKind  kind;

  union Data{
    int  integer;

    std::string  identifier;

    Node*  node;

     Data(int  i=0): integer(i){}
     Data(std::string&&  s): identifier(std::move(s)){}
     Data(Node*  nd): node(nd){}
    ~Data(){}

  } data;


  Operand();
  Operand(std::string&&  s);
  Operand(int  i);
  Operand(Node*  nd);
  Operand(const Operand&  rhs);
  Operand(Operand&&  rhs) noexcept;
  ~Operand();


  Operand&  operator=(const Operand&   rhs);
  Operand&  operator=(      Operand&&  rhs) noexcept;

  void  clear();

  static Value  calculate_node(const Node*  nd);
  static void  print_node(const Node*  nd);
  static void  print_objects();

  void  print() const;


};


#endif




