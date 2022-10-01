cmake_minimum_required(VERSION 3.23)

project(CLionTest1)

set(CMAKE_CXX_STANDARD 14)

set(test_srcs ./main.cpp)

add_executable(CLionTest1 ${test_srcs})

target_link_libraries(CLionTest1 pthread)
