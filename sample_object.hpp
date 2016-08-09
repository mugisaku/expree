#ifndef SAMPLE_OBJECT_HPP_INCLUDED
#define SAMPLE_OBJECT_HPP_INCLUDED


#include<string>
#include<vector>
#include<cstdio>


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif




struct
Object
{
  std::string  identifier;

  int  integer;

  std::vector<Object*>  member_list;


Object&
operator[](const std::string&  id)
{
    for(auto  ptr: member_list)
    {
        if(ptr->identifier == id)
        {
          return *ptr;
        }
    }


  auto  obj = new Object;

  obj->identifier = id;
  obj->integer    =  0;

  member_list.emplace_back(obj);

  return *obj;
}


~Object()
{
    for(auto  ptr: member_list)
    {
      delete ptr;
    }
}


void
print() const
{
    if(identifier.size())
    {
      printf("%s",identifier.data());

      printf(" = %d",integer);
    }


    if(member_list.size())
    {
      printf("{\n");

        for(auto  ptr: member_list)
        {
          ptr->print();

          printf("\n");
        }


      printf("}\n");
    }
}


};




#endif




