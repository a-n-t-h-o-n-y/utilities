# FIND GTEST
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
find_package(GTest REQUIRED)
add_library(gtest INTERFACE IMPORTED)
set_property(TARGET gtest PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
set_property(TARGET gtest PROPERTY
    INTERFACE_LINK_LIBRARIES ${GTEST_BOTH_LIBRARIES})

# CREATE TESTS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_executable(tests
    unsigned_integer_test.cpp
    strong_guarantee_test.cpp
    smf_call_counter_class_test.cpp
    smf_call_counter_array_test.cpp
    smf_call_counter_builtin_test.cpp
    smf_call_counter_aggregate_test.cpp
    type_info_test.cpp
    trait_conjunction_test.cpp
    trait_disjunction_test.cpp
    compound_trait_test.cpp
    property_test.cpp
    duration_view_test.cpp
    thousands_seperator_test.cpp
    primes.test.cpp
    from_file.test.cpp
    to_file.test.cpp
    # async_trigger_test.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(tests PRIVATE gtest libutility ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(tests PRIVATE cxx_std_17)
target_compile_options(tests PRIVATE -Wall)

add_test(tests tests)
