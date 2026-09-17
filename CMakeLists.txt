cmake_minimum_required(VERSION 3.10)
project(revision_cpp_14_days CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(DAYS
    day01_references_const
    day02_const_pointers_members
    day03_raii
    day04_rule_of_three
    day05_unique_ptr
    day06_move_part1
    day07_move_part2
    day08_shared_ptr
    day09_weak_ptr
    day10_enable_shared_from_this
    day11_lambdas_part1
    day12_lambdas_part2
    day13_std_function
    day14_deferred_queue
)

foreach(target ${DAYS})
    add_executable(${target} days/${target}.cpp)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic)
    endif()
endforeach()
