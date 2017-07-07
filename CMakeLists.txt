cmake_minimum_required(VERSION 2.8)


if(DEFINED SLP)
else()
  set(SLP "0")
endif()


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "  sleep ${SLP};  CCACHE_DIR=/tmp/ccachedir ccache")
endif(CCACHE_FOUND)


set(CMAKE_VERBOSE_MAKEFILE ON)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


set(CMAKE_C_COMPILER  gcc)
set(CMAKE_C_FLAGS   "-std=c14 -Werror")
set(CMAKE_CXX_COMPILER  "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Werror")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++")


set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS}   -O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -g")




set(SOURCES
  expree_element.cpp
  expree_element__make_value.cpp
  expree_operand.cpp
  expree_scope.cpp
  expree_primitive.cpp
  expree_object.cpp
  expree_object__operate.cpp
  expree_MemorySpace.cpp
  expree_parser.cpp
  expree_parser__make_element.cpp
)


include_directories(.)
#add_library("libexpree.so" ${SOURCES})
add_executable("testExpree${EXTENSION}" test_expree.cpp ${SOURCES})




