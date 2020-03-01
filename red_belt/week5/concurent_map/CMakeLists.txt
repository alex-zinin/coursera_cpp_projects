cmake_minimum_required(VERSION 3.14)
project(concurent_map)

set(CMAKE_CXX_STANDARD 17)

add_executable(concurent_map main.cpp profile.h test_runner.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(concurent_map Threads::Threads)