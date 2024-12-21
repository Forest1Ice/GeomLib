cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(PROJECT_NAME NURBSLib)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

# unit test option
option(ENABLE_UNIT_TESTS "Enable unit tests" OFF)
if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()