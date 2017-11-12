#!/usr/bin/python
from os import makedirs

def create_cmake():
    cmake = open('CMakeLists.txt', 'w')
    cmake_contents = (
            r'cmake_minimum_required(VERSION 2.6)''\n'
            r'set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g '
            r'-Werror")''\n'
            r'add_executable(main main.cpp)''\n\n'
            r'find_package(Boost)''\n'
            r'if (Boost_FOUND)''\n'
            r'    include_directories(${Boost_INCLUDE_DIRS})''\n'
            r'    target_link_libraries(main ${Boost_LIBRARIES})''\n'
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

if __name__ == '__main__':
    create_cmake()
    create_main()
    create_build_dir()
