cmake_minimum_required(VERSION 2.8)

project(iod_symbol)

SET(CMAKE_CXX_STANDARD 14)

enable_testing()

add_executable(test_symbol test.cc)
add_test(test_symbol test_symbol)

install(DIRECTORY symbol DESTINATION include/iod
  FILES_MATCHING PATTERN "*.hh")
install(DIRECTORY symbol DESTINATION include/iod
  FILES_MATCHING PATTERN "*.hpp")
