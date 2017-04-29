cmake_minimum_required(VERSION 3.7)
project(sdizo_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Graph.cpp Graph.h GraphMatrix.cpp GraphMatrix.h GraphList.cpp GraphList.h)
add_executable(sdizo_2 ${SOURCE_FILES})