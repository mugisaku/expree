#include"expree_operand.hpp"
#include"expree_element.hpp"
#include<cstring>
#include<string>
#include<vector>
#include<new>




Operand::Operand(                ): kind(OperandKind::null      ){}
Operand::Operand(std::string&&  s): kind(OperandKind::identifier){new(&data) std::string(std::move(s));}
Operand::Operand(unsigned int   i): kind(OperandKind::integer   ){new(&data) unsigned int(i);}
Operand::Operand(Element*       e): kind(OperandKind::element   ){data.element = e;}

Operand::Operand(const Operand&  rhs) noexcept:kind(OperandKind::null){*this = rhs;}
Operand::Operand(     Operand&&  rhs) noexcept:kind(OperandKind::null){*this = std::move(rhs);}


Operand::
~Operand()
{
  clear();
}




Operand&
Operand::
operator=(const Operand&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
      case(OperandKind::identifier):
        new(&data.identifier) std::string(rhs.data.identifier);
        break;
      case(OperandKind::integer):
        data.integer = rhs.data.integer;
        break;
      case(OperandKind::element):
        data.element = new Element(*rhs.data.element);
        break;
    }


  return *this;
}


Operand&
Operand::
operator=(Operand&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = OperandKind::null;

    switch(kind)
    {
      case(OperandKind::identifier):
        new(&data.identifier) std::string(std::move(rhs.data.identifier));
        break;
      case(OperandKind::integer):
        data.integer = rhs.data.integer;
        break;
      case(OperandKind::element):
        data.element = rhs.data.element;
        break;
    }


  return *this;
}


void
Operand::
clear()
{
    switch(kind)
    {
      case(OperandKind::identifier):
        data.identifier.~basic_string();
        break;
      case(OperandKind::integer):
        break;
      case(OperandKind::element):
        delete data.element;
        break;
    }


  kind = OperandKind::null;
}


void
Operand::
print() const
{
    switch(kind)
    {
      case(OperandKind::identifier):
        printf("%s",data.identifier.data());
        break;
      case(OperandKind::integer):
        printf("%u",data.integer);
        break;
      case(OperandKind::element):
        printf("(");

        auto  l = data.element->get_left();
        auto  r = data.element->get_right();

          if(l){l->print();}

        data.element->print();

          if(r){r->print();}

        printf(")");
        break;
    }
}




