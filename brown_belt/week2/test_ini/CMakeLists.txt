cmake_minimum_required(VERSION 3.14)
project(test_ini)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_ini main.cpp test_runner.h ini.h ini.cpp)