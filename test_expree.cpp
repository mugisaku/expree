#include"expree_node.hpp"
#include<cstring>
#include<cctype>
#include<vector>




int
main(int  argc, char**  argv)
{
  Value  a(Integer(0xFF));
  Value  b(Integer(4));

  auto  c = a<<b;

  printf("%X\n",c->integer.data);

  return 0;
}




