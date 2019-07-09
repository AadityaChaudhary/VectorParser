cmake_minimum_required(VERSION 3.14)
project(VectorParser)
project(TestParser)

set(CMAKE_CXX_STANDARD 14)

add_executable(VectorParser main.cpp parser.cpp parser.h)
add_executable(TestParser test.cpp parser.cpp parser.h)