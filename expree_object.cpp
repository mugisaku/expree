#include"expree_object.hpp"
#include<new>
#include<cstring>




Object::Object(): kind(ObjectKind::undefined){}
Object::Object(const Null&  n): kind(ObjectKind::null){}
Object::Object(const Void&  v): kind(ObjectKind::void_){}
Object::Object(const Pointer&  p): kind(ObjectKind::pointer){data.pointer = p;}
Object::Object(const Integer&  i): kind(ObjectKind::integer){data.integer = i;}
Object::Object(const Boolean&  b): kind(ObjectKind::boolean){data.boolean = b;}
Object::Object(const Reference&  r): kind(ObjectKind::reference){new(&data) Reference(r);}
Object::Object(const Object&   rhs) noexcept: kind(ObjectKind::null){*this = rhs;}
Object::Object(      Object&&  rhs) noexcept: kind(ObjectKind::null){*this = std::move(rhs);}


Object::
~Object()
{
  clear();
}




Object&
Object::
operator=(const Object&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

  std::memcpy(&data,&rhs.data,sizeof(data));
}


Object&
Object::
operator=(Object&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                   ;
         rhs.kind = ObjectKind::null;

  std::memcpy(&data,&rhs.data,sizeof(data));
}


void
Object::
clear()
{
  kind = ObjectKind::null;
}




void
Object::
print() const
{
    switch(kind)
    {
  case(ObjectKind::null):
      printf(" NULL ");
      break;
  case(ObjectKind::void_):
      printf(" VOID ");
      break;
  case(ObjectKind::undefined):
      printf(" UNDEFINED ");
      break;
  case(ObjectKind::integer):
      data.integer.print();
      break;
  case(ObjectKind::boolean):
      data.boolean.print();
      break;
  case(ObjectKind::pointer):
      data.pointer.print();
      break;
  case(ObjectKind::reference):
      data.reference.get_pointer().print();
      break;
    }
}




