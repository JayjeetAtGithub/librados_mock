cmake_minimum_required(VERSION 3.16.3)
project(rados_mock)

set(CMAKE_CXX_STANDARD 14)

add_executable(rados_mock test.cpp example_framework.cpp)
target_link_libraries(rados_mock gmock gtest rados pthread)