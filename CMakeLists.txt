cmake_minimum_required(VERSION 2.8)

project(iod_symbol)

SET(CMAKE_CXX_STANDARD 14)

enable_testing()

add_executable(test_symbol test.cc)
add_test(test_symbol test_symbol)
