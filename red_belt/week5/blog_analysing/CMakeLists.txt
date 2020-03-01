cmake_minimum_required(VERSION 3.14)
project(blog_analysing)

set(CMAKE_CXX_STANDARD 17)


add_executable(blog_analysing main.cpp test_runner.h profile.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(blog_analysing Threads::Threads)