cmake_minimum_required(VERSION 3.14)
project(web_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(web_server main.cpp http_request.h stats.h stats.cpp)