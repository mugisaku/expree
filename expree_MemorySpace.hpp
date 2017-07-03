#ifndef expree_MemorySpace_HPP_INCLUDED
#define expree_MemorySpace_HPP_INCLUDED


#include<vector>
#include<string>


struct Object;




struct
Link
{
  int  index;

  std::string  name;

};


class
MemorySpace
{
  std::vector<Object>  object_table;

public:
  MemorySpace();

  Object&  get_object(int  i);

  Link  make_object();

};


#endif




