#include"expree_parser.hpp"
#include"expree_scope.hpp"
#include<cstring>
#include<cctype>
#include<vector>




int
main(int  argc, char**  argv)
{
  std::string  s("x + 32");

  Parser  p(s);

  auto  e = p.make_element();


  MemorySpace  memsp;

  Scope  scope(memsp);

  e.print();

  printf(" == ");

  e.make_value(&scope).print();

  printf("\n");


  return 0;
}




