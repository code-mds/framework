cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(framework)

add_subdirectory("${PROJECT_SOURCE_DIR}/serie1" )
add_subdirectory("${PROJECT_SOURCE_DIR}/serie2" )
add_subdirectory("${PROJECT_SOURCE_DIR}/serie3" )
add_subdirectory("${PROJECT_SOURCE_DIR}/TodoList" )
add_subdirectory("${PROJECT_SOURCE_DIR}/teoria" )
add_subdirectory("${PROJECT_SOURCE_DIR}/test" )