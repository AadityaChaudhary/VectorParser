cmake_minimum_required(VERSION 3.14)
project(VectorParser)

set(CMAKE_CXX_STANDARD 14)

add_executable(VectorParser main.cpp parser.cpp parser.h)