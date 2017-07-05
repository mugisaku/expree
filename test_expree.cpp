#include"expree_parser.hpp"
#include"expree_scope.hpp"
#include"expree_MemorySpace.hpp"
#include<cstring>
#include<cctype>
#include<vector>


using namespace expree;


int
main(int  argc, char**  argv)
{
  std::string  s("x = ( 32+ 8 )");
  std::string  s2("x = 32");

  Parser  p(s);

  auto  e = p.make_element();


  MemorySpace  memsp;

  auto&  gloscp = memsp.get_global_scope();

  e.print();

  printf(" == ");

  e.make_value(&gloscp,true).print();

  printf("\n");

  printf("\n");
if(2)
{
  p.reset(s2);

  p.start();

  e = p.make_element();

  e.print();

  printf(" == ");

auto  res =  e.make_value(&gloscp,false);

 res.print();

  printf("\n");
}



  return 0;
}




