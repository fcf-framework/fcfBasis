
cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME fcfBasisTest)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Ob1 /GL /LTCG")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
  endif()
  message("MSVC")
else()
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # -Og оптимизирует код, сохраняя отладочную информацию, вместо -fno-inline-functions
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O0 -g")
  else()
    # -march=native использует возможности конкретного CPU
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native -flto")
    # Применяем флаги релиза к текущей сборке, если это не Release (на случай явного вызова)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
       # Обычно для Release flags задаются глобально или через set_target_properties,
       # но здесь мы добавляем базовые оптимизации к общему флагу если это не debug
       set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG") 
    endif()
  endif()
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
  #set(CMAKE_CXX_FLAGS_RELEASE "-O4")
endif()





include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/test/libraries)

add_subdirectory(./test/tests)

