cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(PROJECT_NAME NURBSLIB)
project(${PROJECT_NAME})

option(ENABLE_UNIT_TESTS "Enable unit tests" OFF)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()