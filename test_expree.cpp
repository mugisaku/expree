#include"expree.hpp"
#include"sample_element.hpp"
#include<cstring>
#include<cctype>




using namespace expree;


void
skip_spaces(const char*&  p)
{
    while(isspace(*p))
    {
      ++p;
    }
}


template<typename  T>
bool
try_read_operator(std::vector<Element>&  ls, const char*&  p, const T&  op)
{
  auto  len = std::strlen(op.codes);

    if(std::strncmp(p,op.codes,len) == 0)
    {
      ls.emplace_back(op);

      p += len;

      return true;
    }


  return false;
}


bool
try_read_unary_operator(std::vector<Element>&  ls, const char*&  p)
{
       if(try_read_operator(ls,p,UnaryOperator('-'))){}
  else if(try_read_operator(ls,p,UnaryOperator('!'))){}
  else if(try_read_operator(ls,p,UnaryOperator('~'))){}
  else {return false;}


  return true;
}


bool
try_read_binary_operator(std::vector<Element>&  ls, const char*&  p)
{
       if(try_read_operator(ls,p,BinaryOperator('<','<','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('<','<'))){}
  else if(try_read_operator(ls,p,BinaryOperator('<','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('<'))){}
  else if(try_read_operator(ls,p,BinaryOperator('>','>','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('>','>'))){}
  else if(try_read_operator(ls,p,BinaryOperator('>','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('>'))){}
  else if(try_read_operator(ls,p,BinaryOperator('=','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('='))){}
  else if(try_read_operator(ls,p,BinaryOperator('!','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('!'))){}
  else if(try_read_operator(ls,p,BinaryOperator('|','|'))){}
  else if(try_read_operator(ls,p,BinaryOperator('|','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('|'))){}
  else if(try_read_operator(ls,p,BinaryOperator('&','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('&','&'))){}
  else if(try_read_operator(ls,p,BinaryOperator('&'))){}
  else if(try_read_operator(ls,p,BinaryOperator('^','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('^'))){}
  else if(try_read_operator(ls,p,BinaryOperator('+','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('+'))){}
  else if(try_read_operator(ls,p,BinaryOperator('-','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('-'))){}
  else if(try_read_operator(ls,p,BinaryOperator('*','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('*'))){}
  else if(try_read_operator(ls,p,BinaryOperator('/','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('/'))){}
  else if(try_read_operator(ls,p,BinaryOperator('%','='))){}
  else if(try_read_operator(ls,p,BinaryOperator('%'))){}
  else if(try_read_operator(ls,p,BinaryOperator('.'))){}
  else {return false;}


  return true;
}


std::vector<Element>
scan_expression(const char*&  p, char  end);


bool
try_read_operand(std::vector<Element>&  ls, const char*&  p)
{
  auto  c = *p;

    if(c == '(')
    {
      auto  subls = scan_expression(++p,')');

      auto  rpn = to_rpn(std::move(subls));

      auto  nd = create_tree(std::move(rpn));

      ls.emplace_back(Operand(nd));

      return true;
    }

  else
    if(isalpha(c) || (c == '_'))
    {
      std::string  id;

      id.push_back(*p++);

        while(isalnum(*p) || (*p == '_'))
        {
          id.push_back(*p++);
        }


      ls.emplace_back(Operand(std::move(id)));

      return true;
    }

  else
    {
      int  i = 0;

        while(isdigit(*p))
        {
          i *= 10;

          i += *p++-'0';
        }


      ls.emplace_back(Operand(i));

      return true;
    }


  return false;
}


bool
try_read_unary_operand(std::vector<Element>&  ls, const char*&  p)
{
  std::vector<Element>  buf;

  auto  start = p;

    while(try_read_unary_operator(buf,p))
    {
      skip_spaces(p);
    }


  skip_spaces(p);

    if(try_read_operand(buf,p))
    {
        for(auto&  el: buf)
        {
          ls.emplace_back(std::move(el));
        }


      return true;
    }


  p = start;

  return false;
}


std::vector<Element>
scan_expression(const char*&  p, char  end)
{
  std::vector<Element>  ls;

  skip_spaces(p);

    if(try_read_unary_operand(ls,p))
    {
        for(;;)
        {
          skip_spaces(p);

            if(*p == end)
            {
              ++p;

              break;
            }


            if(!try_read_binary_operator(ls,p))
            {
printf("error1\n");

              break;
            }


          skip_spaces(p);

            if(!try_read_unary_operand(ls,p))
            {
printf("error2\n");
              break;
            }
        }
    }


  return std::move(ls);
}


void
scan(const char*  p)
{
  printf("ソース: %s\n",p);


  auto  rpn = to_rpn(scan_expression(p,0));

  printf("RPN: ");

    for(auto  nd: rpn)
    {
      nd->element.print(true);
    }


  printf("\n");


  auto  nd = create_tree(std::move(rpn));

  printf("結果: ");

  Operand::print_node(nd);

  auto  v = Operand::calculate_node(nd);

  printf(" = %d\n\n",*v);

  delete nd;
}


int
main(int  argc, char**  argv)
{
    if(argc > 1)
    {
        for(int  i = 1;  i < argc;  i += 1)
        {
          scan(argv[i]);
        }
    }

  else
    {
        for(;;)
        {
          char  buf[1024];

          printf("expree_test>");

          fgets(buf,sizeof(buf),stdin);

            if(std::strncmp(buf,"\n",1) == 0)
            {
              break;
            }

          else
            if(std::strncmp(buf,"q",1) == 0)
            {
              break;
            }

          else
            if(std::strncmp(buf,"p",1) == 0)
            {
              Operand::print_objects();
            }

          else
            {
              scan(buf);
            }
        }
    }


  return 0;
}




