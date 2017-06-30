#include"expree_parser.hpp"
#include<cctype>
#include<cstring>




struct
Parser::
Node
{
  BlockMark  block_mark;

  Element*  element=nullptr;

  Node*  first=nullptr;
  Node*   last=nullptr;

  Node*  previous=nullptr;
  Node*      next=nullptr;

   Node(Operand&&   o): element(new Element(std::move(o))){}
   Node(Operator    o): element(new Element(         (o))){}
   Node(BlockMark  bm, Node*  first_, Node*  last_): block_mark(bm), first(first_), last(last_){}
  ~Node()
   {
     delete element;

     auto  now = first;

       while(now)
       {
         auto  next = now->next;

         delete now            ;
                now = now->next;
       }
   }


  void  print() const
  {
      if(element){element->print();}
    else
      {
        auto  next = first;

        printf("%c",block_mark.begin);

          while(next)
          {
            next->print();

            next = next->next;
          }


        printf("%c",block_mark.end);
      }
  }

};




Parser::
Parser(const std::string&  s):
row_count(0),
head(s.data()),
current(s.data()),
end(s.data()+s.size()),
first(nullptr),
last(nullptr)
{
  start();
}


Parser::
Parser(Parser&  parent, BlockMark  blk_mark):
row_count(parent.row_count),
head(parent.head),
current(parent.current),
end(parent.end),
block_mark(blk_mark),
first(nullptr),
last(nullptr)
{
  start();

  parent.row_count = row_count;
  parent.head      = head;
  parent.current   = current+1;

  parent.push(new Node(block_mark,first,last));

  first = nullptr;
}


Parser::
~Parser()
{
  auto  ptr = first;

    while(ptr)
    {
      auto  next = ptr->next;

      delete ptr       ;
             ptr = next;
    }
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
push(Node*  nd)
{
    if(!first)
    {
      first = nd;
       last = nd;
    }

  else
    {
      last->next = nd                      ;
                   nd->previous = last     ;
                                  last = nd;
    }
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

          push(new Node(Operand(u)));

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
      std::string  s;

      s.push_back(c);

      ++current;

        while(!test_end())
        {
          auto  c = get_char();

          ++current;

            if(!isalnum(c) && (c != '_'))
            {
              break;
            }


          s.push_back(c);
        }


      push(new Node(Operand(std::move(s))));

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

      push(new Node(o));

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
      else if(read_operator(Operator('+','='))){}
      else if(read_operator(Operator('+'))){}
      else if(read_operator(Operator('-','='))){}
      else if(read_operator(Operator('-'))){}
      else if(read_operator(Operator('*','='))){}
      else if(read_operator(Operator('*'))){}
      else if(read_operator(Operator('/','='))){}
      else if(read_operator(Operator('/'))){}
      else if(read_operator(Operator('%','='))){}
      else if(read_operator(Operator('%'))){}
      else if(read_operator(Operator('.'))){}
      else if(read_block(BlockMark('(',')'))){}
      else if(read_block(BlockMark('[',']'))){}
      else if(read_block(BlockMark('<','>'))){}
      else
        {
          printf("不明な要素: %c\n",get_char());

          break;
        }
    }
}


void
Parser::
print() const
{
  auto  ptr = first;

    while(ptr)
    {
      ptr->print();

      ptr = ptr->next;
    }
}




