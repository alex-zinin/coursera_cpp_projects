cmake_minimum_required(VERSION 3.14)
project(concurrent_map2)

set(CMAKE_CXX_STANDARD 17)

add_executable(concurrent_map2 main.cpp test_runner.h profile.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(concurrent_map2 Threads::Threads)