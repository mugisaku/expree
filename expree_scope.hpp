#ifndef EXPREE_Scope_HPP_INCLUDED
#define EXPREE_Scope_HPP_INCLUDED


#include<string>
#include<list>
#include"expree_MemorySpace.hpp"
#include"expree_primitive.hpp"
#include"expree_object.hpp"




struct
Scope
{
  MemorySpace&  space;

  Scope*  const parent=nullptr;

  std::list<Link>  link_table;

  Scope(MemorySpace&   space_): space(space_       ), parent( nullptr){}
  Scope(Scope&        parent_): space(parent_.space), parent(&parent_){}

  Object&   get_object(const std::string&  name);
  Object*  find_object(const std::string&  name);

  Pointer      get_pointer(const std::string&  name                              ) const;
  Reference  get_reference(const std::string&  name, bool  new_if_found_not=false)      ;

};


#endif




