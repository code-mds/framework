cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(teoria)

add_executable(${PROJECT_NAME} main.cpp frazione.cpp)
