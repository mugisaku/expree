#include"expree_parser.hpp"
#include<cstring>
#include<cctype>
#include<vector>




int
main(int  argc, char**  argv)
{
  std::string  s(" (2 + 8-- *~5)");

  Parser  p(s);

  p.make_element().print();


  return 0;
}




