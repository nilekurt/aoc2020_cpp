project(aoc2020_common VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE INC "include/*.hh")
file(GLOB_RECURSE SRC "src/*.cc")

add_library(aoc2020_common)
target_sources(aoc2020_common PRIVATE ${INC} ${SRC})
target_include_directories(aoc2020_common
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(aoc2020_common
    PUBLIC absl::container
    PRIVATE aoc2020_copts_common)

configure_lto(aoc2020_common)
configure_tidy(aoc2020_common)
