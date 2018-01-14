#!/usr/bin/python
from os import makedirs

def create_cmake():
    cmake = open('CMakeLists.txt', 'w')
    cmake_contents = (
            r'cmake_minimum_required(VERSION 3.2)''\n\n'

            r'# set(CMAKE_BUILD_TYPE Release)''\n'
            r'set(CMAKE_BUILD_TYPE Debug)''\n'
            r'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")''\n\n'

            r'# set(LIBRARY_SOURCES ''\n'
            r'# )''\n'
            r'# add_library(newlib STATIC ${LIBRARY_SOURCES})''\n'
            r'add_executable(main main.cpp)''\n'
            r'# target_link_libraries(main newlib)''\n\n'

            r'find_package(Boost)''\n'
            r'if (Boost_FOUND)''\n'
            r'    include_directories(${Boost_INCLUDE_DIRS})''\n'
            r'    target_link_libraries(main ${Boost_LIBRARIES})''\n'
            r'endif()''\n\n'

            r'# Unit Tests''\n'
            r'enable_testing()''\n'
            r'set(TEST_SOURCES''\n'
            r'    "test.cpp"''\n'
            r')''\n'
            r'find_package(GTest REQUIRED)''\n'
            r'if (GTEST_FOUND)''\n'
            r'    add_executable(utests ${TEST_SOURCES})''\n'
            r'    target_link_libraries(utests ${GTEST_BOTH_LIBRARIES})''\n'
            r'#     target_link_libraries(utests newlib)''\n'
            r'    add_test(NAME unit_tests COMMAND utests)''\n'
            r'endif()''\n'
            )


    cmake.write(cmake_contents)
    cmake.close()

def create_main():
    main = open('main.cpp', 'w')
    main_contents = (
            r'#include <iostream>''\n\n'
            r'int main(int argc, const char* argv[]) {''\n'
            r'    return 0;''\n'
            r'}''\n'
            )
    main.write(main_contents)
    main.close()

def create_build_dir():
    makedirs('build')

def create_test():
    test = open('test.cpp', 'w')
    test_contents = (
            r'#include <gtest/gtest.h>''\n\n'
            r'TEST(TestGroup, TestName) {''\n'
            r'    ASSERT_TRUE(true);''\n'
            r'    EXPECT_EQ(true, true);''\n'
            r'}''\n'
            )
    test.write(test_contents)
    test.close()

if __name__ == '__main__':
    create_cmake()
    create_main()
    create_build_dir()
    create_test()
