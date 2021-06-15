cmake_minimum_required(VERSION 3.10)


PROJECT(HelloWorld)

include(/home/vagrant/softwares/parasoft/cpptest/10.5/integration/cmake/cmake/cpptest.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/logger/inc/public)
ADD_EXECUTABLE(hello ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/hello.cpp)

message(status ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src/logger)

cpptest_add_executable(
hello_test 
CPPTEST_COMPILER_ID 
    gcc_7-64
CPPTEST_PROJECT_LOC 
    ${CMAKE_CURRENT_SOURCE_DIR}
CPPTEST_PROJECT_FOLDERS 
    HELLO_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}
SOURCES main.cpp src/hello.cpp
)
#SOURCES 
   # main.cpp src/hello.cpp src/logger/src/Logger.cpp
