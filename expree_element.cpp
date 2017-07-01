#include"expree_element.hpp"
#include<new>




Element::Element(): kind(ElementKind::null), left(nullptr), right(nullptr){}
Element::Element(Operand&&                    o): kind(ElementKind::operand), left(nullptr), right(nullptr){new(&data) Operand(std::move(o));}
Element::Element(const             Operator&  o): kind(ElementKind::operator_ ){new(&data) Operator(o);}
Element::Element(const  PrefixUnaryOperator&  o): kind(ElementKind::prefix_unary_operator ), left(nullptr), right(nullptr){new(&data) Operator(o);}
Element::Element(const  SuffixUnaryOperator&  o): kind(ElementKind::suffix_unary_operator ), left(nullptr), right(nullptr){new(&data) Operator(o);}
Element::Element(const BinaryOperator&        o): kind(ElementKind::binary_operator), left(nullptr), right(nullptr){new(&data) Operator(o);}

Element::Element(const Element&   rhs) noexcept: kind(ElementKind::null), left(nullptr), right(nullptr){*this = rhs;}
Element::Element(      Element&&  rhs) noexcept: kind(ElementKind::null), left(nullptr), right(nullptr){*this = std::move(rhs);}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(const Element&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

   left = rhs.left ? new Element(*rhs.left ):nullptr;
  right = rhs.right? new Element(*rhs.right):nullptr;

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

  std::swap( left,rhs.left );
  std::swap(right,rhs.right);

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


  delete left          ;
         left = nullptr;

  delete right          ;
         right = nullptr;

  kind = ElementKind::null;
}




void
Element::
insert_to_left(Element*  e)
{
  delete left    ;
         left = e;
}


void
Element::
insert_to_right(Element*  e)
{
  delete right    ;
         right = e;
}




void
Element::
print() const
{
    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.print();
        break;
      case(ElementKind::operator_):
        data.operator_.print();
        break;
      case(ElementKind::prefix_unary_operator):
        printf("(");
        data.operator_.print();
        left->print();
        printf(")");
        break;
      case(ElementKind::suffix_unary_operator):
        printf("(");
        left->print();
        data.operator_.print();
        printf(")");
        break;
      case(ElementKind::binary_operator):
        printf("(");
        left->print();
        data.operator_.print();
        right->print();
        printf(")");
        break;
    }
}




