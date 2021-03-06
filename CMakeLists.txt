cmake_minimum_required(VERSION 3.17)
project(NES)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(HELPER_FUNCTIONS)

include_directories("./include")

# file(GLOB_RECURSE source "src/*.cpp")
add_library("CPU6502" STATIC 
            "src/bus.cpp" "include/bus.hpp"
            "src/catridge.cpp" "include/catridge.hpp"
            "src/cpu6502.cpp" "include/cpu6502.hpp"
            "src/ppu2C02.cpp" "include/ppu2C02.hpp" 
            "include/header.hpp" 
            "include/mapper.hpp" "src/mapper.cpp" 
            "include/mapper_000.hpp" "src/mapper_000.cpp")

add_executable("NES_CPU" "cpu_test.cpp")
add_executable("OLC" "olc_example.cpp")

target_link_libraries("NES_CPU" "CPU6502")

if (APPLE)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

target_link_libraries("OLC" "-framework OpenGL" "-framework GLUT" "-framework Carbon" ${PNG_LIBRARY})
target_link_libraries("NES_CPU" "CPU6502" "-framework OpenGL" "-framework GLUT" "-framework Carbon" ${PNG_LIBRARY})

else()

target_link_libraries("NES_CPU" "CPU6502")

endif()