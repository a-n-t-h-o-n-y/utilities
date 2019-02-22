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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(utility_tests # EXCLUDE_FROM_ALL
    # async_trigger_test.cpp
    unsigned_integer.test.cpp
    strong_guarantee.test.cpp
    smf_call_counter_class.test.cpp
    smf_call_counter_array.test.cpp
    smf_call_counter_builtin.test.cpp
    smf_call_counter_aggregate.test.cpp
    type_info.test.cpp
    trait_conjunction.test.cpp
    trait_disjunction.test.cpp
    compound_trait.test.cpp
    property.test.cpp
    duration_view.test.cpp
    thousands_seperator.test.cpp
    primes.test.cpp
    from_file.test.cpp
    to_file.test.cpp
    memory_view.test.cpp
    narrow_cast.test.cpp
    random_value.test.cpp
    bit_array.test.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(utility_tests
    PRIVATE
        gtest
        libutility
        ${CMAKE_THREAD_LIBS_INIT}
)
target_compile_features(utility_tests PRIVATE cxx_std_17)
target_compile_options(utility_tests PRIVATE -Wall -Wextra)

add_test(NAME utility COMMAND utility_tests)
