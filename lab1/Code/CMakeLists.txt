cmake_minimum_required(VERSION 3.1.0)

project(lab1 CXX)

IF(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(external/benchmark)



add_executable(lab_1 main_benchmark.cpp levenstein.cpp matrix.cpp)

include_directories(external/benchmark/include)

target_include_directories(lab_1 PRIVATE external)
target_link_libraries(lab_1 PRIVATE benchmark)
