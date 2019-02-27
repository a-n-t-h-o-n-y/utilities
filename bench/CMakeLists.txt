# Benchmarks
add_executable(utility_bench
    primes.bench.cpp
)

target_compile_features(utility_bench PRIVATE cxx_std_17)
target_compile_options(utility_bench PRIVATE -Wall -Wextra)
target_link_libraries(utility_bench libutility benchmark_main)

add_custom_target(bench_baseline
    ${CMAKE_BINARY_DIR}/bench/utility_bench --benchmark_out=bench_baseline.json
    --benchmark_out_format=json
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Making initial benchmark" VERBATIM)

add_custom_target(bench_compare
    python2 ${CMAKE_SOURCE_DIR}/external/benchmark/tools/compare.py benchmarks
    ${CMAKE_BINARY_DIR}/bench_baseline.json
    ${CMAKE_BINARY_DIR}/bench/utility_bench
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Making new benchmarck and comparing to baseline" VERBATIM)
