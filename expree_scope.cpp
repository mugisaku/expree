#include"expree_scope.hpp"




Object&
Scope::
get_object(const std::string&  name)
{
  auto  result = find_object(name);

    if(!result)
    {
      auto  ln = space.make_object();

      ln.name = name;

      link_table.emplace_back(std::move(ln));

      result = &space.get_object(ln.index);
    }


  return *result;
}


Object*
Scope::
find_object(const std::string&  name)
{
    for(auto&  ln: link_table)
    {
        if(ln.name == name)
        {
          return &space.get_object(ln.index);
        }
    }


  return parent? parent->find_object(name):nullptr;
}


Pointer
Scope::
get_pointer(const std::string&  name) const
{
    for(auto&  ln: link_table)
    {
        if(ln.name == name)
        {
          return Pointer(ln.index);
        }
    }


  return parent? parent->get_pointer(name):Pointer();
}


Reference
Scope::
get_reference(const std::string&  name, bool  new_if_found_not)
{
  auto  ptr = get_pointer(name);

    if(ptr)
    {
      return Reference(space,ptr.data);
    }

  else
    if(new_if_found_not)
    {
    }


  throw Exception("参照が見つかりませんでした");
}






