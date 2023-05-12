cmake_minimum_required(VERSION 3.20)

project(example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

include(FetchContent)
FetchContent_Declare(fixed-size-hash
    GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/..
    GIT_TAG HEAD
)
FetchContent_MakeAvailable(fixed-size-hash)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE fixed-size-hash)

