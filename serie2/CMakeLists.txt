cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(serie2)

add_executable(${PROJECT_NAME} s2main.cpp Convertitore.cpp)
