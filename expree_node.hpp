#ifndef EXPREE_node_HPP_INCLUDED
#define EXPREE_node_HPP_INCLUDED


#include"expree_element.hpp"
#include"expree_value.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


struct Scope;


class
Node
{
  Element  element;

  Node*   left;
  Node*  right;

public:
  Node(                   );
  Node(      Element&&  el);
  Node(const Element&   el);

  Node(      Node&&  rhs) noexcept;
  Node(const Node&   rhs) noexcept;

  ~Node();


  Node&  operator=(const Node&   rhs) noexcept;
  Node&  operator=(      Node&&  rhs) noexcept;

  void  clear();

  Value  make_value(Scope&  scope) const;

  void  print() const;

};


#endif




