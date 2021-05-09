cmake_minimum_required(VERSION 3.17)
project(NES)

add_compile_definitions(HELPER_FUNCTIONS)
include_directories("./include")

file(GLOB_RECURSE source "src/*.cpp")
add_library("CPU6502" STATIC ${source})

add_executable("NES_CPU" "cpu_test.cpp")

add_executable("OLC" "olc_example.cpp")

target_link_libraries("NES_CPU" "CPU6502")