cmake_minimum_required(VERSION 3.1.0)
project(unittest)

include_directories(../src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "--coverage")
# Now simply link against gtest or gtest_main as needed. 

add_executable(utest test_test.cc)
target_link_libraries(utest gtest_main)
target_link_libraries(utest sphere)
enable_testing()