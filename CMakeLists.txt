cmake_minimum_required(VERSION 2.8)


if(DEFINED SLEEPING_TIME)
else()
  set(SLEEPING_TIME "0")
endif()


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "  sleep ${SLEEPING_TIME};  CCACHE_DIR=/tmp/ccachedir ccache")
endif(CCACHE_FOUND)


set(CMAKE_VERBOSE_MAKEFILE ON)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


set(CMAKE_C_COMPILER  gcc)
set(CMAKE_C_FLAGS   "-std=c14 -Werror")
set(CMAKE_CXX_COMPILER  "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Werror")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++ -lz -lpng -lSDL2 -lSDL2_image -lSDL2main")


set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS}   -Og -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -Og -g")


if(EM)
  set(EXTENSION ".html")
  set(CMAKE_CXX_COMPILER  em++)
  set(CMAKE_CXX_FLAGS "-std=c++14 -Werror -Wno-switch -O2")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 --preload-file expandmetal.png --preload-file lena_std.png --use-preload-plugins")
endif()




set(SOURCES
  expree_element.cpp
  expree_operand.cpp
  expree_node.cpp
  expree_scope.cpp
  expree_value.cpp
  expree_integer.cpp
  expree_reference.cpp
)


include_directories(.)
#add_library("libexpree.so" ${SOURCES})
add_executable("testExpree${EXTENSION}" test_expree.cpp ${SOURCES})


if(EM)
#  set_target_properties("testTextureRenderingContext${EXTENSION}" PROPERTIES LINK_FLAGS "--shell-file ../shell__tTRC.html")
endif()




