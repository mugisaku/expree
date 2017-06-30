#include"expree_node.hpp"
#include"expree_value.hpp"
#include"expree_scope.hpp"




Node::
Node():
left(nullptr),
right(nullptr)
{
}


Node::
Node(Element&&  el):
element(std::move(el)),
left(nullptr),
right(nullptr)
{
}


Node::
Node(const Element&  el):
element(el),
left(nullptr),
right(nullptr)
{
}


Node::
Node(Node&&  rhs) noexcept:
left(nullptr),
right(nullptr)
{
  *this = std::move(rhs);
}


Node::
Node(const Node&  rhs) noexcept:
left(nullptr),
right(nullptr)
{
  *this = rhs;
}


Node::
~Node()
{
  clear();
}




Node&
Node::
operator=(const Node&  rhs) noexcept
{
  clear();

  element = rhs.element;

   left = rhs.left ? new Node(*rhs.left ):nullptr;
  right = rhs.right? new Node(*rhs.right):nullptr;

  return *this;
}


Node&
Node::
operator=(Node&&  rhs) noexcept
{
  clear();

  element = std::move(rhs.element);

  std::swap( left,rhs.left );
  std::swap(right,rhs.right);

  return *this;
}




void
Node::
clear()
{
  delete left          ;
         left = nullptr;

  delete right          ;
         right = nullptr;
}





Value
Node::
make_value(Scope&  scope) const
{
    switch(element.get_kind())
    {
      case(ElementKind::null):
        break;
      case(ElementKind::operand):
        {
          auto&  op = element->operand;

            switch(op.get_kind())
            {
              case(OperandKind::identifier):
                return Value(Reference(scope.get_value(op->identifier)));
                break;
              case(OperandKind::expression):
                return op->expression->make_value(scope);
                break;
              case(OperandKind::integer):
                return Value(Integer(op->integer));
                break;
            }
        }
        break;
      case(ElementKind::unary_operator):
        {
          auto  v = left->make_value(scope);

            switch(element->operator_)
            {
              case(Operator('!')): v = Value(!v);break;
              case(Operator('~')): v = Value(~v);break;
              case(Operator('-')): v = Value(-v);break;
            }


          return v;
        }
        break;
      case(ElementKind::binary_operator):
        {
          auto  op = element->operator_;

          auto  lv =  left->make_value(scope);
          auto  rv = right->make_value(scope);

            switch(op)
            {
              case(Operator('*')): lv = Value(lv*rv);break;
              case(Operator('/')): lv = Value(lv/rv);break;
              case(Operator('%')): lv = Value(lv%rv);break;

              case(Operator('+')): lv = Value(lv+rv);break;
              case(Operator('-')): lv = Value(lv-rv);break;

              case(Operator('<','<')): lv = Value(lv<<rv);break;
              case(Operator('>','>')): lv = Value(lv>>rv);break;

              case(Operator('<')    ): lv = Value(lv< rv);break;
              case(Operator('<','=')): lv = Value(lv<=rv);break;
              case(Operator('>')    ): lv = Value(lv> rv);break;
              case(Operator('>','=')): lv = Value(lv>=rv);break;

              case(Operator('=','=')): lv = Value(lv==rv);break;
              case(Operator('!','=')): lv = Value(lv!=rv);break;


              case(Operator('&')): lv = Value(lv&rv);break;
              case(Operator('|')): lv = Value(lv|rv);break;
              case(Operator('^')): lv = Value(lv^rv);break;

              case(Operator('&','&')): lv = Value(lv&&rv);break;
              case(Operator('|','|')): lv = Value(lv&&rv);break;

              case(Operator('<','<','=')): lv <<= rv;break;
              case(Operator('>','>','=')): lv >>= rv;break;
              case(Operator(    '+','=')): lv  += rv;break;
              case(Operator(    '-','=')): lv  -= rv;break;
              case(Operator(    '*','=')): lv  *= rv;break;
              case(Operator(    '/','=')): lv  /= rv;break;
              case(Operator(    '%','=')): lv  %= rv;break;
              case(Operator(    '&','=')): lv  &= rv;break;
              case(Operator(    '|','=')): lv  |= rv;break;
              case(Operator(    '^','=')): lv  ^= rv;break;
              case(Operator(        '=')): lv   = rv;break;
            }


          return lv;
        }
        break;
    }


  return Value(Undefined());
}




void
Node::
print() const
{
    switch(element.get_kind())
    {
      case(ElementKind::null):
        break;
      case(ElementKind::operand):
        element.print();
        break;
      case(ElementKind::unary_operator):
        printf("(");

        element.print();

        left->print();

        printf(")");
        break;
      case(ElementKind::binary_operator):
        printf("(");
 
        left->print();

        element.print();

        right->print();

        printf(")");
        break;
    }
}




