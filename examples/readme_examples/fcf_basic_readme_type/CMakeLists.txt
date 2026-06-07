cmake_minimum_required(VERSION 3.10)
project(fcf_basic_readme_type)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)

add_executable(fcf_basic_readme_type main.cpp)
