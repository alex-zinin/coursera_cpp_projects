cmake_minimum_required(VERSION 3.14)
project(Stats_Aggregator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Stats_Aggregator main.cpp stats_aggregator.h stats_aggregator.cpp stats_aggregator_test.cpp test_runner.h)