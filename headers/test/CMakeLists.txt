cmake_minimum_required(VERSION 3.2)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

# Unit Tests
enable_testing()
set(TEST_SOURCES
    "unsigned_integer_test.cpp"
    "strong_guarantee_test.cpp"
    "smf_call_counter_test.cpp"
)
find_package(GTest REQUIRED)
if (GTEST_FOUND)
    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests ${GTEST_BOTH_LIBRARIES})
    add_test(NAME unit_tests COMMAND tests)
endif()
