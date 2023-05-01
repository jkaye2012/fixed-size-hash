cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

project(fixed-size-hash)

add_library(fixed-size-hash INTERFACE)
target_include_directories(fixed-size-hash INTERFACE include/)

add_subdirectory(tests)
