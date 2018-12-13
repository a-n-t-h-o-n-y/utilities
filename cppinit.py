#!/usr/bin/python
from os import makedirs

def create_cmake():
    cmake_file = open('CMakeLists.txt', 'w')
    cmake_contents = (
            r'cmake_minimum_required(VERSION 3.2)''\n\n'

            r'add_executable(main main.cpp)''\n'
            r'target_compile_features(main PRIVATE cxx_std_17)''\n'
            r'target_compile_options(main PRIVATE -Wall -Wextra)''\n\n'

            r'find_package(Boost)''\n'
            r'if (Boost_FOUND)''\n'
            r'    target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})''\n'
            r'    target_link_libraries(main ${Boost_LIBRARIES})''\n'
            r'endif()''\n\n'
            )
    cmake_file.write(cmake_contents)
    cmake_file.close()

def create_main():
    main_file = open('main.cpp', 'w')
    main_contents = (
            r'#include <iostream>''\n\n'
            r'int main(int argc, const char* argv[]) {''\n'
            r'    return 0;''\n'
            r'}''\n'
            )
    main_file.write(main_contents)
    main_file.close()

def create_build_dir():
    makedirs('build')

if __name__ == '__main__':
    create_cmake()
    create_main()
    create_build_dir()
