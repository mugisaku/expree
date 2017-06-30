#ifndef EXPREE_Scope_HPP_INCLUDED
#define EXPREE_Scope_HPP_INCLUDED


#include<string>
#include<vector>
#include"expree_value.hpp"




struct
Object
{
  std::string  name;

  Value  value;

  Object(const std::string&  name_, Value&&  v):
  name(name_), value(std::move(v)){}

};


struct
Scope
{
  Scope*  const parent=nullptr;

  std::vector<Object>  object_table;

  Scope(Scope*  parent_=nullptr): parent(parent_){}

  Value&     get_value(const std::string&  name                 );
  Value*    find_value(const std::string&  name                 );
  Value*  update_value(const std::string&  name, const Value&  v);

};


#endif




