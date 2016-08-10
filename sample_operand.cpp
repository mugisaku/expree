#include"sample_operand.hpp"
#include"sample_element.hpp"
#include"expree.hpp"
#include<cstring>
#include<string>
#include<vector>
#include<new>




namespace{


Object
root_object;


}


Operand::
Operand():
kind(OperandKind::null),
data(0)
{
}


Operand::
Operand(std::string&&  s):
kind(OperandKind::identifier),
data(std::move(s))
{
}


Operand::
Operand(int  i):
kind(OperandKind::integer),
data(i)
{
}


Operand::
Operand(Node*  nd):
kind(OperandKind::node),
data(nd)
{
}


Operand::
Operand(const Operand&  rhs):
kind(OperandKind::null)
{
  *this = rhs;
}


Operand::
Operand(Operand&&  rhs) noexcept:
kind(OperandKind::null)
{
  *this = std::move(rhs);
}


Operand::
~Operand()
{
  clear();
}




Operand&
Operand::
operator=(const Operand&  rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
      case(OperandKind::identifier):
        new(&data.identifier) std::string(rhs.data.identifier);
        break;
      case(OperandKind::node):
        data.node = new Node(*rhs.data.node);
        break;
      case(OperandKind::integer):
        data.integer = rhs.data.integer;
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
      case(OperandKind::node):
        data.node = rhs.data.node;
        break;
      case(OperandKind::integer):
        data.integer = rhs.data.integer;
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
      case(OperandKind::node):
        delete data.node;
        break;
      case(OperandKind::integer):
        break;
    }


  kind = OperandKind::null;
}


void
Operand::
print_node(const Node*  nd)
{
    switch(nd->element.kind)
    {
      case(ElementKind::null):
        print_node(nd->left);
        break;
      case(ElementKind::operand):
        nd->element.print();
        break;
      case(ElementKind::unary_operator):
        printf("(");

        nd->element.print();

        print_node(nd->left);

        printf(")");
        break;
      case(ElementKind::binary_operator):
        printf("(");
 
        print_node(nd->left);

        nd->element.print();

        print_node(nd->right);

        printf(")");
        break;
    }
}


Value
Operand::
calculate_node(const Node*  nd)
{
    switch(nd->element.kind)
    {
      case(ElementKind::null):
        return calculate_node(nd->left);
        break;
      case(ElementKind::operand):
        {
          auto&  op = nd->element.data.operand;

            switch(op.kind)
            {
              case(OperandKind::identifier):
                return Value(&root_object[op.data.identifier]);
                break;
              case(OperandKind::node):
                return calculate_node(op.data.node);
                break;
              case(OperandKind::integer):
                return Value(op.data.integer);
                break;
            }
        }
        break;
      case(ElementKind::unary_operator):
        {
          auto  v = calculate_node(nd->left);

          auto&  l = *v;

            switch(nd->element.data.operator_)
            {
              case(Operator('!')): v = Value(!l);break;
              case(Operator('~')): v = Value(~l);break;
              case(Operator('-')): v = Value(-l);break;
            }


          return v;
        }
        break;
      case(ElementKind::binary_operator):
        {
          auto  op = nd->element.data.operator_;

          auto  lv = calculate_node(nd->left);
          auto&  l = *lv;

          auto&  ro = nd->right->element.data.operand;

            switch(op)
            {
              case(Operator('.')):
                {
                    if(!lv.object)
                    {
                      printf("左辺がオブジェクトではありません\n");

                      throw;
                    }


                    if(ro.kind != OperandKind::identifier)
                    {
                      printf("右辺が識別子ではありません\n");

                      throw;
                    }


                  return Value(&(*lv.object)[ro.data.identifier]);
                }
                break;
            }


          auto  rv = calculate_node(nd->right);
          auto&  r = *rv;

            switch(op)
            {
              case(Operator('*')): lv = Value(l*r);break;
              case(Operator('/')): lv = Value(l/r);break;
              case(Operator('%')): lv = Value(l%r);break;

              case(Operator('+')): lv = Value(l+r);break;
              case(Operator('-')): lv = Value(l-r);break;

              case(Operator('<','<')): lv = Value(l<<r);break;
              case(Operator('>','>')): lv = Value(l>>r);break;

              case(Operator('<')    ): lv = Value(l< r);break;
              case(Operator('<','=')): lv = Value(l<=r);break;
              case(Operator('>')    ): lv = Value(l> r);break;
              case(Operator('>','=')): lv = Value(l>=r);break;

              case(Operator('=','=')): lv = Value(l==r);break;
              case(Operator('!','=')): lv = Value(l!=r);break;


              case(Operator('&')): lv = Value(l&r);break;
              case(Operator('|')): lv = Value(l|r);break;
              case(Operator('^')): lv = Value(l^r);break;

              case(Operator('&','&')): lv = Value(l&&r);break;
              case(Operator('|','|')): lv = Value(l&&r);break;

              case(Operator('<','<','=')): l <<= r;break;
              case(Operator('>','>','=')): l >>= r;break;
              case(Operator('+','=')): l += r;break;
              case(Operator('-','=')): l -= r;break;
              case(Operator('*','=')): l *= r;break;
              case(Operator('/','=')): l /= r;break;
              case(Operator('%','=')): l %= r;break;
              case(Operator('&','=')): l &= r;break;
              case(Operator('|','=')): l |= r;break;
              case(Operator('^','=')): l ^= r;break;
              case(Operator('=')    ): l  = r;break;
            }


          return lv;
        }
        break;
    }


  return Value(0);
}


void
Operand::
print_objects()
{
  printf("%d個のオブジェクトがあります\n",root_object.member_list.size());

  root_object.print();
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
      case(OperandKind::node):
        print_node(data.node);
        break;
      case(OperandKind::integer):
        printf("%d",data.integer);
        break;
    }
}




