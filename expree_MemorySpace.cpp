#include"expree_MemorySpace.hpp"
#include"expree_object.hpp"




MemorySpace::
MemorySpace()
{
  object_table.emplace_back(Object());
}




Object&
MemorySpace::
get_object(int  i)
{
  return object_table[i];
}


Link
MemorySpace::
make_object()
{
  Link  ln;

  ln.index = object_table.size();

  object_table.emplace_back(Object());

  return std::move(ln);
}




