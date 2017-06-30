#include"expree_scope.hpp"




Value*
Scope::
update_value(const std::string&  name, const Value&  v)
{
    for(auto&  o: object_table)
    {
        if(o.name == name)
        {
          o.value = v;

          return &o.value;
        }
    }


    if(parent)
    {
      auto  result = parent->update_value(name,v);

        if(result)
        {
          return result;
        }
    }


  object_table.emplace_back(name,Value(v));

  return &object_table.back().value;
}


Value&
Scope::
get_value(const std::string&  name)
{
  auto  result = find_value(name);

    if(!result)
    {
      object_table.emplace_back(name,Value(Undefined()));

      result = &object_table.back().value;
    }


  return *result;
}


Value*
Scope::
find_value(const std::string&  name)
{
    for(auto&  o: object_table)
    {
        if(o.name == name)
        {
          return &o.value;
        }
    }


  return parent? parent->find_value(name):nullptr;
}




