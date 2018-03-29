cmake_minimum_required(VERSION 2.8)

project(Operator)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")    #-fno-elide-constructors

set(SOURCE_FILES Main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
