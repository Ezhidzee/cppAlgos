cmake_minimum_required(VERSION 3.25)
project(cppAlgos)

set(CMAKE_CXX_STANDARD 23)

add_executable(cppAlgos tests.cpp ezhidzeAlgorithm.hpp xrange.hpp zip.hpp)

add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)
target_link_libraries(cppAlgos gtest gtest_main)