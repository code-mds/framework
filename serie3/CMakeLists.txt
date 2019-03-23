cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(serie3)

add_executable(${PROJECT_NAME} s3main.cpp frazione.cpp s3e2.cpp)
