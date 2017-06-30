#include"expree_element.hpp"
#include<new>




Element::Element():kind(ElementKind::null){}
Element::Element(Operand&&  o):kind(ElementKind::operand){new(&data) Operand(std::move(o));}
Element::Element(const  UnaryOperator&  o): kind(ElementKind::unary_operator ){new(&data) Operator(o);}
Element::Element(const BinaryOperator&  o): kind(ElementKind::binary_operator){new(&data) Operator(o);}

Element::Element(const Element&   rhs) noexcept:kind(ElementKind::null){*this = rhs;}
Element::Element(      Element&&  rhs) noexcept:kind(ElementKind::null){*this = std::move(rhs);}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(const Element&   rhs) noexcept
{
  clear();

  kind = rhs.kind;

    if(kind == ElementKind::operand)
    {
      new(&data.operand) Operand(rhs.data.operand);
    }

  else
    {
      data.operator_ = rhs.data.operator_;
    }
}


Element&
Element::
operator=(Element&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

    if(kind == ElementKind::operand)
    {
      new(&data.operand) Operand(std::move(rhs.data.operand));
    }

  else
    {
      data.operator_ = rhs.data.operator_;
    }
}


void
Element::
clear()
{
    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.~Operand();
        break;
    }


  kind = ElementKind::null;
}


void
Element::
print(bool  parenthesis) const
{
    if(parenthesis)
    {
      printf("(");
    }


    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.print();
        break;
      case(ElementKind::unary_operator):
      case(ElementKind::binary_operator):
        printf("%s",data.operator_.codes);
        break;
    }


    if(parenthesis)
    {
      printf(")");
    }
}




