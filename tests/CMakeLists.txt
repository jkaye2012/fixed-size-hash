get_filename_component(fixed_root_dir ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY REALPATH)

if(${CMAKE_SOURCE_DIR} STREQUAL ${fixed_root_dir})
  Include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.3.2
  )

  FetchContent_MakeAvailable(Catch2)

  add_executable(tests test.cpp custom_test.cpp)
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  target_link_libraries(tests PRIVATE fixed-size-hash)
endif()