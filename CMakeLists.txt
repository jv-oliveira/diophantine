cmake_minimum_required(VERSION 3.15)
project(diophantine)

set(CMAKE_CXX_STANDARD 17)

add_executable(diophantine main.cpp linear_diophantine_eq.hpp)

target_compile_options(diophantine PRIVATE
        -Werror
        -Wall
        -Wextra
        -Wsuggest-override
        -Wuninitialized
        -Wsign-compare
        -Wdouble-promotion
        -Wmissing-braces
        -Wsequence-point
        -Wfloat-equal
        -Wtype-limits
        -Wredundant-decls
)