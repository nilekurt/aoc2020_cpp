cmake_minimum_required(VERSION 3.14)

project(aoc2020 VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

include(FetchContent)
include(lto.helper)
include(with.helper)
include(tidy.helper)

option(aoc2020_CLANG_TIDY "Build with clang-tidy" ON)
option(LTO "Build with Link-Time Optimization" OFF)

WithMsg(clang-tidy ${aoc2020_CLANG_TIDY})

set(aoc2020_EXTRA_CFLAGS -ffast-math -fvisibility=hidden)

set_property(GLOBAL PROPERTY aoc2020_RELEASE_EXTRA_CFLAGS ${aoc2020_EXTRA_CFLAGS})

add_library(aoc2020_copts_common INTERFACE)
target_compile_options(aoc2020_copts_common INTERFACE
    -W
    -Wall
    -Wextra
    -Wcast-align
    -Wcast-qual
    -Wmissing-declarations
    -Wwrite-strings
    -Wundef
    -Wswitch-enum
    -Wshadow
    -Werror
    -Wstrict-aliasing=2
    $<$<C_COMPILER_ID:Clang>:-Wshadow-all -pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wshadow-all -pedantic>
    $<$<STREQUAL:$<CONFIG>,Debug>:-ggdb>
    $<$<STREQUAL:$<CONFIG>,Release>:${aoc2020_EXTRA_CFLAGS}>)

add_subdirectory(3rdparty)
add_subdirectory(common)
add_subdirectory(problem_1)
add_subdirectory(problem_2)
