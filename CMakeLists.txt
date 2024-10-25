cmake_minimum_required(VERSION 3.14)
project(BitField)

set(CMAKE_CXX_STANDARD 17)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
add_executable(BitField main.cpp
        BitField.cpp
        Set.cpp)
