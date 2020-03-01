cmake_minimum_required(VERSION 3.14)
project(collide)

set(CMAKE_CXX_STANDARD 17)

add_executable(collide main.cpp test_runner.h geo2d.h geo2d.cpp game_object.h)