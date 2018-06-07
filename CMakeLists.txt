project(ctti)
cmake_minimum_required(VERSION 2.8)

option(CTTI_BUILD_TESTS "Build ctti feature tests" OFF)
option(CTTI_BUILD_EXAMPLES "Build ctti examples" OFF)

include(cmake/vs_source_groups.cmake)

set(CTTI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wall -Werror")
endif()

add_library(ctti INTERFACE)
target_include_directories(ctti INTERFACE ${CTTI_SOURCE_DIR}/include)

if(CTTI_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(CTTI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
