#ifndef expree_Parser_HPP_INCLUDED
#define expree_Parser_HPP_INCLUDED


#include<string>
#include<utility>
#include<vector>
#include"expree_element.hpp"


struct
BlockMark
{
  int  begin;
  int    end;

  constexpr BlockMark(int  bg=0, int  ed=0):
  begin(bg),
  end(ed){}

};


class
Parser
{
  int  row_count;

  const char*     head;
  const char*  current;
  const char*      end;

  BlockMark  block_mark;

  std::vector<Element>  buffer;

  void  skip_spaces();
  void  advance(int  n=1);
  void  newline();

  int  get_char() const{return *current;}

  bool  read_identifier();
  bool  read_number();
  bool    read_operator(Operator  o);
  bool    read_block(BlockMark  blk_mark);

  bool  test_end() const;

  void  start();

public:
  Parser(const std::string&  s);
  Parser(Parser&  parent, BlockMark  blk_mark);

  Element  make_element() const;

};


#endif




