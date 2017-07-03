#include"expree_element.hpp"
#include"expree_scope.hpp"
#include"expree_primitive.hpp"




Object
Element::
make_value(Scope*  scope) const
{
    switch(get_kind())
    {
      case(ElementKind::null):
        throw Exception("空の要素です");
        break;
      case(ElementKind::operand):
        {
          auto&  op = data.operand;

            switch(op.get_kind())
            {
              case(OperandKind::identifier):
                  if(!scope)
                  {
                    throw Exception("スコープのない計算で、識別子が使用されました");
                  }


                return Object(scope->get_reference(op->string));
                break;
              case(OperandKind::element):
                return op->element->make_value(scope);
                break;
              case(OperandKind::integer_literal):
                return Object(Integer(op->integer));
                break;
              case(OperandKind::string_literal):
                break;
            }
        }
        break;
      case(ElementKind::prefix_unary_operator):
        {
          auto  v = left->make_value(scope);

            switch(*data.operator_)
            {
              case(*Operator('!')): return Object::log_not(v);break;
              case(*Operator('~')): return Object::bit_not(v);break;
              case(*Operator('-')): return Object::neg(v);break;
/*
              case(*Operator('*')): return v;break;
              case(*Operator('&')): return v;break;
              case(*Operator('+','+')): return ;break;
              case(*Operator('-','-')): return ;break;
*/
            }
        }
        break;
      case(ElementKind::suffix_unary_operator):
        {
/*
          auto  v = left->make_left_value(scope);

            switch(*data.operator_)
            {
              case(*Operator('+','+')): v = Value(!v);break;
              case(*Operator('-','-')): v = Value(!v);break;
            }
*/
        }
        break;
      case(ElementKind::binary_operator):
        {
          auto  rv = right->make_value(scope);
          auto  lv =  left->make_value(scope);

            switch(*data.operator_)
            {
              case(*Operator('*')): return Object::ari_mul(lv,rv);
              case(*Operator('/')): return Object::ari_div(lv,rv);
              case(*Operator('%')): return Object::ari_rem(lv,rv);

              case(*Operator('+')): return Object::ari_add(lv,rv);
              case(*Operator('-')): return Object::ari_sub(lv,rv);

              case(*Operator('<','<')): return Object::bit_shl(lv,rv);
              case(*Operator('>','>')): return Object::bit_shr(lv,rv);

              case(*Operator('<')    ): return Object::cmp_lt(lv,rv);
              case(*Operator('<','=')): return Object::cmp_lteq(lv,rv);
              case(*Operator('>')    ): return Object::cmp_gt(lv,rv);
              case(*Operator('>','=')): return Object::cmp_gteq(lv,rv);

              case(*Operator('=','=')): return Object::cmp_eq( lv,rv);
              case(*Operator('!','=')): return Object::cmp_neq(lv,rv);


              case(*Operator('&')): return Object::bit_and(lv,rv);
              case(*Operator('|')): return Object::bit_or( lv,rv);
              case(*Operator('^')): return Object::bit_xor(lv,rv);

              case(*Operator('&','&')): return Object::log_and(lv,rv);
              case(*Operator('|','|')): return Object::log_or( lv,rv);
/*

              case(*Operator('<','<','=')): return Object::(lv <<= rv);
              case(*Operator('>','>','=')): return Object::(lv >>= rv);
              case(*Operator(    '+','=')): return Object::(lv  += rv);
              case(*Operator(    '-','=')): return Object::(lv  -= rv);
              case(*Operator(    '*','=')): return Object::(lv  *= rv);
              case(*Operator(    '/','=')): return Object::(lv  /= rv);
              case(*Operator(    '%','=')): return Object::(lv  %= rv);
              case(*Operator(    '&','=')): return Object::(lv  &= rv);
              case(*Operator(    '|','=')): return Object::(lv  |= rv);
              case(*Operator(    '^','=')): return Object::(lv  ^= rv);
              case(*Operator(        '=')): return Object::(lv   = rv);
*/
            }
        }
        break;
    }


  return Object();
}




