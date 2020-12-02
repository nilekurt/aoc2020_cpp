project(aoc2020_problem_1 VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE INC "include/*.hh")
file(GLOB_RECURSE SRC "src/*.cc")

add_executable(aoc2020_problem_1)
target_sources(aoc2020_problem_1 PRIVATE ${INC} ${SRC})
target_link_libraries(aoc2020_problem_1
    PRIVATE
    aoc2020_copts_common 
    aoc2020_common
    absl::raw_hash_set
    absl::hash
    GSL)

configure_lto(aoc2020_problem_1)
configure_tidy(aoc2020_problem_1)

