cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(.)

add_executable(ft_containers
        main.cpp
        map.hpp
        stack.hpp
        vector.hpp
        iterator.hpp
        type_traits.hpp)
