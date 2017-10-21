cmake_minimum_required(VERSION 2.8)

project(StringTrivial)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-elide-constructors")    #-fno-elide-constructors

set(SOURCE_FILES StringTrivialtest.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
