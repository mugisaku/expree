#include"expree_parser.hpp"
#include<cctype>
#include<cstring>




Parser::
Parser(const std::string&  s):
row_count(0),
head(s.data()),
current(s.data()),
end(s.data()+s.size())
{
  start();

if(0)
{
    for(auto&  e:buffer)
    {
      e.print();
    }
}
}


Parser::
Parser(Parser&  parent, BlockMark  blk_mark):
row_count(parent.row_count),
head(parent.head),
current(parent.current),
end(parent.end),
block_mark(blk_mark)
{
  start();

  parent.row_count = row_count;
  parent.head      = head;
  parent.current   = current+1;

  parent.buffer.emplace_back(make_element());
}




bool
Parser::
test_end() const
{
  auto  c = get_char();

  return((current >= end) || (c == block_mark.end));
}


void
Parser::
skip_spaces()
{
    while(!test_end())
    {
      auto  c = get_char();

        if(!isspace(c))
        {
          break;
        }


      advance();
    }
}


void
Parser::
newline()
{
  head = current;

  ++row_count;
}


void
Parser::
advance(int  n)
{
    while(n--)
    {
      auto  c = get_char();

        if(test_end())
        {
          break;
        }


      ++current;

        if(c == '\n')
        {
          newline();
        }
    }
}


bool
Parser::
read_number()
{
  auto  c = get_char();

    if(isdigit(c))
    {
      unsigned int  u;

      int  n;

        if(sscanf(current,"%u%n",&u,&n) >= 1)
        {
          current += n;

          buffer.emplace_back(Operand(u));

          return true;
        }

      else
        {
          return false;
        }
    }


  return false;
}


bool
Parser::
read_identifier()
{
  auto  c = get_char();

    if(isalpha(c) || (c == '_'))
    {
      Identifier  id;

      id.string.push_back(c);

      ++current;

        while(!test_end())
        {
          auto  c = get_char();

          ++current;

            if(!isalnum(c) && (c != '_'))
            {
              break;
            }


          id.string.push_back(c);
        }


      buffer.emplace_back(Operand(std::move(id)));

      return true;
    }


  return false;
}


bool
Parser::
read_operator(Operator  o)
{
  const char*  str = o.codes;

  auto  len = std::strlen(str);

    if(std::strncmp(current,str,len) == 0)
    {
      current += len;

      buffer.emplace_back(o);

      return true;
    }


  return false;
}


bool
Parser::
read_block(BlockMark  blk_mark)
{
  auto  c = get_char();

    if(c == blk_mark.begin)
    {
      ++current;

      Parser  child(*this,blk_mark);

      return true;
    }


  return false;
}


void
Parser::
start()
{
    for(;;)
    {
      skip_spaces();

        if(test_end())
        {
          break;
        }

           if(read_identifier()){}
      else if(read_number()){}
      else if(read_operator(Operator('<','<','='))){}
      else if(read_operator(Operator('<','<'))){}
      else if(read_operator(Operator('<','='))){}
      else if(read_operator(Operator('<'))){}
      else if(read_operator(Operator('>','>','='))){}
      else if(read_operator(Operator('>','>'))){}
      else if(read_operator(Operator('>','='))){}
      else if(read_operator(Operator('>'))){}
      else if(read_operator(Operator('=','='))){}
      else if(read_operator(Operator('='))){}
      else if(read_operator(Operator('!','='))){}
      else if(read_operator(Operator('!'))){}
      else if(read_operator(Operator('|','|'))){}
      else if(read_operator(Operator('|','='))){}
      else if(read_operator(Operator('|'))){}
      else if(read_operator(Operator('&','='))){}
      else if(read_operator(Operator('&','&'))){}
      else if(read_operator(Operator('&'))){}
      else if(read_operator(Operator('^','='))){}
      else if(read_operator(Operator('^'))){}
      else if(read_operator(Operator('+','+'))){}
      else if(read_operator(Operator('+','='))){}
      else if(read_operator(Operator('+'))){}
      else if(read_operator(Operator('-','-'))){}
      else if(read_operator(Operator('-','>','*'))){}
      else if(read_operator(Operator('-','>'))){}
      else if(read_operator(Operator('-','='))){}
      else if(read_operator(Operator('-'))){}
      else if(read_operator(Operator('*','='))){}
      else if(read_operator(Operator('*'))){}
      else if(read_operator(Operator('/','='))){}
      else if(read_operator(Operator('/'))){}
      else if(read_operator(Operator('%','='))){}
      else if(read_operator(Operator('%'))){}
      else if(read_operator(Operator('.','*'))){}
      else if(read_operator(Operator('.'))){}
      else if(read_operator(Operator('~'))){}
      else if(read_operator(Operator(','))){}
      else if(read_block(BlockMark('(',')'))){}
      else if(read_block(BlockMark('[',']'))){}
      else if(read_block(BlockMark('<','>'))){}
      else if(read_block(BlockMark(':',':'))){}
      else
        {
          printf("不明な要素: %c\n",get_char());

          break;
        }
    }
}




