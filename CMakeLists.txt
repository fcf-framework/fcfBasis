cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME fcfBasisTest)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
  message("MSVC")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
  #set(CMAKE_CXX_FLAGS_RELEASE "-O4")
endif()

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/test/libraries)

add_subdirectory(./test/tests)

