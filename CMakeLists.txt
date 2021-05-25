cmake_minimum_required(VERSION 3.5.1)


PROJECT(HelloWorld)
include_directories(inc)



ADD_EXECUTABLE(hello main.cpp src/hello.cpp)
