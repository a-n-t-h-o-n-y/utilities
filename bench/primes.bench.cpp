#include <utility/primes.hpp>

#include <benchmark/benchmark.h>

namespace {

void gen_hundred(benchmark::State& state) {
    for (auto _ : state) {
        utility::generate_primes<100>();
    }
}
BENCHMARK(gen_hundred);

void gen_thousand(benchmark::State& state) {
    for (auto _ : state) {
        utility::generate_primes<1'000>();
    }
}
BENCHMARK(gen_thousand);

void gen_million(benchmark::State& state) {
    for (auto _ : state) {
        utility::generate_primes<1'000'000>();
    }
}
BENCHMARK(gen_million);

void gen_ten_million(benchmark::State& state) {
    for (auto _ : state) {
        utility::generate_primes<10'000'000>();
    }
}
BENCHMARK(gen_ten_million);

}  // namespace
