#include"expree_parser.hpp"
#include"expree_rearrange.hpp"
#include<cstring>
#include<cctype>
#include<vector>




int
main(int  argc, char**  argv)
{
  std::string  s(" (2 + 8 )");

  Parser  p(s);

  p.print();

  Value  a(Integer(0xFF));
  Value  b(Integer(4));

  auto  c = a<<b;

  printf("\n%X\n",c->integer.data);

  return 0;
}




