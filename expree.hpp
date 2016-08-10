#ifndef EXPREE_HPP_INCLUDED
#define EXPREE_HPP_INCLUDED


#include<vector>
#include<list>
#include<cstdio>


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace expree{


enum class
ElementKind
{
  null,
  operand,
  unary_operator,
  binary_operator,

};


enum class
Associativity
{
  none,
  left_to_right,
  right_to_left,

};


struct
Precedence
{
  int  number;

  constexpr Precedence(int  n=0): number(n){}

};


template<typename  E>
struct
Node
{
  using Element = E;

  Element  element;

  Node*   left;
  Node*  right;


Node():
left(nullptr),
right(nullptr)
{
}


Node(Element&&  el) noexcept:
element(std::move(el)),
left(nullptr),
right(nullptr)
{
}


Node(const Element&  el):
element(el),
left(nullptr),
right(nullptr)
{
}


Node(Node&&  rhs) noexcept:
left(nullptr),
right(nullptr)
{
  *this = std::move(rhs);
}


Node(const Node&  rhs):
left(nullptr),
right(nullptr)
{
  *this = rhs;
}


~Node()
{
  clear();
}




Node&
operator=(const Node&  rhs)
{
  clear();

  element = rhs.element;

   left = rhs.left ? new Node(*rhs.left ):nullptr;
  right = rhs.right? new Node(*rhs.right):nullptr;

  return *this;
}


Node&
operator=(Node&&  rhs)
{
  clear();

  element = std::move(rhs.element);

  std::swap( left,rhs.left );
  std::swap(right,rhs.right);

  return *this;
}


void
clear()
{
  delete left          ;
         left = nullptr;

  delete right          ;
         right = nullptr;
}


};


template<typename  E>
void
merge(std::list<Node<E>*>&  buf, std::vector<E>&  uols)
{
  auto  it = uols.rbegin();
  auto end = uols.rend();

    while(it != end)
    {
      buf.emplace_back(new Node<E>(std::move(*it++)));
    }
}


template<typename  E>
std::list<Node<E>*>
to_rpn(std::vector<E>&&  src)
{
  std::list<Node<E>*>  dst;

  std::vector<E>   unary_operator_stack;
  std::vector<E>  binary_operator_stack;

    for(auto&  el: src)
    {
        switch(static_cast<ElementKind>(el))
        {
          case(ElementKind::unary_operator):
            unary_operator_stack.emplace_back(el);
            break;
          case(ElementKind::binary_operator):
            {
              auto  cur_preced = static_cast<Precedence>(el).number;

                if(unary_operator_stack.size())
                {
                  auto  tail_preced = static_cast<Precedence>(unary_operator_stack.back()).number;

                    if(cur_preced >= tail_preced)
                    {
                        for(auto&  unop: unary_operator_stack)
                        {
                          binary_operator_stack.emplace_back(std::move(unop));
                        }
                    }

                  else
                    {
                      merge(dst,unary_operator_stack);
                    }


                  unary_operator_stack.clear();
                }


                while(binary_operator_stack.size())
                {
                  auto&  tail = binary_operator_stack.back();

                  auto  tail_preced = static_cast<Precedence>(tail).number;

                    if(cur_preced <= tail_preced)
                    {
                        if((cur_preced == tail_preced) &&
                           (static_cast<Associativity>(tail) == Associativity::right_to_left))
                        {
                          break;
                        }

                      else
                        {
                          dst.emplace_back(new Node<E>(std::move(tail)));

                          binary_operator_stack.pop_back();
                        }
                    }

                  else
                    {
                      break;
                    }
                }


  	           binary_operator_stack.emplace_back(el);
            }
            break;
          case(ElementKind::operand):
            dst.emplace_back(new Node<E>(std::move(el)));
            break;
        }
    }


  merge(dst, unary_operator_stack);
  merge(dst,binary_operator_stack);

  return std::move(dst);
}


template<typename  E>
Node<E>*
create_tree(std::list<Node<E>*>&&  ls)
{
  std::vector<Node<E>*>  operand_buf;

    while(ls.size())
    {
      auto  nd = ls.front();
                 ls.pop_front();

        switch(static_cast<ElementKind>(nd->element))
        {
          case(ElementKind::operand):
            operand_buf.emplace_back(nd);
            break;
          case(ElementKind::unary_operator):
              if(operand_buf.size() < 1)
              {
                printf("単項演算オペランドの数が足りません\n");
                throw;
              }


            nd->left = operand_buf.back();

            operand_buf.pop_back();
            operand_buf.emplace_back(nd);
            break;
          case(ElementKind::binary_operator):
              if(operand_buf.size() < 2)
              {
                printf("二項演算オペランドの数が足りません\n");
                throw;
              }


            nd->right = operand_buf.back();

            operand_buf.pop_back();

            nd->left = operand_buf.back();

            operand_buf.pop_back();


            operand_buf.emplace_back(nd);
            break;
        }
    }


    if(operand_buf.size() != 1)
    {
      printf("結果が不正でした\n");
      throw;
    }


  return operand_buf.front();
}


}


#endif




