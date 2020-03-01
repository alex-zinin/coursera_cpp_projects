cmake_minimum_required(VERSION 3.14)
project(raii_booking)

set(CMAKE_CXX_STANDARD 17)

add_executable(raii_booking main.cpp new_trip_manager.h test_runner.h new_booking_providers.h booking.h)