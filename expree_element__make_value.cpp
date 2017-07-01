#include"expree_element.hpp"
#include"expree_scope.hpp"




Value
Element::
make_value(Scope&  scope) const
{
    switch(get_kind())
    {
      case(ElementKind::null):
        break;
      case(ElementKind::operand):
        {
          auto&  op = data.operand;

            switch(op.get_kind())
            {
              case(OperandKind::identifier):
                return Value(Reference(scope.get_value(op->identifier)));
                break;
              case(OperandKind::element):
                return op->element->make_value(scope);
                break;
              case(OperandKind::integer):
                return Value(Integer(op->integer));
                break;
            }
        }
        break;
      case(ElementKind::prefix_unary_operator):
        {
          auto  v = left->make_value(scope);

            switch(*data.operator_)
            {
              case(*Operator('!')): v = Value(!v);break;
              case(*Operator('~')): v = Value(~v);break;
              case(*Operator('-')): v = Value(-v);break;
              case(*Operator('*')): v = Value(-v);break;
              case(*Operator('&')): v = Value(-v);break;
              case(*Operator('+','+')): v = Value(!v);break;
              case(*Operator('-','-')): v = Value(!v);break;
            }


          return v;
        }
        break;
      case(ElementKind::suffix_unary_operator):
        {
          auto  v = left->make_value(scope);

            switch(*data.operator_)
            {
              case(*Operator('+','+')): v = Value(!v);break;
              case(*Operator('-','-')): v = Value(!v);break;
            }


          return v;
        }
        break;
      case(ElementKind::binary_operator):
        {
          auto  lv =  left->make_value(scope);
          auto  rv = right->make_value(scope);

            switch(*data.operator_)
            {
              case(*Operator('*')): lv = Value(lv*rv);break;
              case(*Operator('/')): lv = Value(lv/rv);break;
              case(*Operator('%')): lv = Value(lv%rv);break;

              case(*Operator('+')): lv = Value(lv+rv);break;
              case(*Operator('-')): lv = Value(lv-rv);break;

              case(*Operator('<','<')): lv = Value(lv<<rv);break;
              case(*Operator('>','>')): lv = Value(lv>>rv);break;

              case(*Operator('<')    ): lv = Value(lv< rv);break;
              case(*Operator('<','=')): lv = Value(lv<=rv);break;
              case(*Operator('>')    ): lv = Value(lv> rv);break;
              case(*Operator('>','=')): lv = Value(lv>=rv);break;

              case(*Operator('=','=')): lv = Value(lv==rv);break;
              case(*Operator('!','=')): lv = Value(lv!=rv);break;


              case(*Operator('&')): lv = Value(lv&rv);break;
              case(*Operator('|')): lv = Value(lv|rv);break;
              case(*Operator('^')): lv = Value(lv^rv);break;

              case(*Operator('&','&')): lv = Value(lv&&rv);break;
              case(*Operator('|','|')): lv = Value(lv&&rv);break;

              case(*Operator('<','<','=')): lv <<= rv;break;
              case(*Operator('>','>','=')): lv >>= rv;break;
              case(*Operator(    '+','=')): lv  += rv;break;
              case(*Operator(    '-','=')): lv  -= rv;break;
              case(*Operator(    '*','=')): lv  *= rv;break;
              case(*Operator(    '/','=')): lv  /= rv;break;
              case(*Operator(    '%','=')): lv  %= rv;break;
              case(*Operator(    '&','=')): lv  &= rv;break;
              case(*Operator(    '|','=')): lv  |= rv;break;
              case(*Operator(    '^','=')): lv  ^= rv;break;
              case(*Operator(        '=')): lv   = rv;break;
            }


          return lv;
        }
        break;
    }


  return Value(Undefined());
}




