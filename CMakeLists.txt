cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(libutility LANGUAGES CXX)
include(GNUInstallDirs)
enable_testing()

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

option(BUILD_BENCHMARK "Build the submodule benchmark library" OFF)

if (BUILD_BENCHMARK)
    # Override default value in benchmark subdirectory.
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF
        CACHE BOOL "Enable building the unit tests which depend on gtest")
    add_subdirectory(external/benchmark)
endif()

add_subdirectory(external/Signals)

# CREATE UTILITY LIBRARY
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_library(libutility INTERFACE)

target_include_directories(libutility
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(libutility INTERFACE signals)
target_include_directories(libutility INTERFACE include/)
target_compile_options(libutility INTERFACE -Wall -Wextra)
target_compile_features(libutility INTERFACE cxx_std_20)

# ADD TESTS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_subdirectory(test)

# ADD BENCHMARKS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
if (BUILD_BENCHMARK)
    add_subdirectory(bench)
endif()

# DOXYGEN
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs-utility
        ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()

