#ifndef UTILITY_PRIMES_HPP
#define UTILITY_PRIMES_HPP
#include <bitset>
#include <cmath>
#include <cstddef>
#include <memory>
#include <vector>

namespace utility {
namespace detail {

/// Return if \p index is even.
inline constexpr bool even(std::size_t index) {
    return index % 2 == 0;
}

/// Returns value corresponding to \p index.
inline constexpr int value_from_index(std::size_t index) {
    if (even(index)) {
        return 5 + index * 3;
    } else {
        return 5 + 2 + (index - 1) * 3;
    }
}

/// Returns the index in the bitset corresponding to \p value.
inline constexpr std::size_t index_from_value(int value) {
    return (value - 4) / 3;
}

/// Thirds a size for a container so that ...
inline constexpr std::size_t third_size(std::size_t limit) {
    return (limit / 3) - 1;
}

// Calculates pi(x), the approximate number of primes up to \p limit.
inline constexpr std::size_t approx_prime_count(int limit) {
    return limit / (std::log(limit) - 1);
}

}  // namespace detail

/// Generates a list of all primes up to, but not including, \p limit.
/** Uses Sieve of Eratosthenes with multiples of 2 and 3 removed. */
template <int limit>
std::vector<int> generate_primes() {
    if constexpr (limit < 2) {
        return {};
    } else if constexpr (limit == 3) {
        return {2};
    }
    using namespace detail;
    const auto sieve_ptr = std::make_unique<std::bitset<third_size(limit)>>();
    const auto sqrt_limit = std::size_t(std::sqrt(sieve_ptr->size()));
    auto result = std::vector<int>{2, 3};
    result.reserve(approx_prime_count(limit));
    for (auto i = std::size_t{0}; i < sieve_ptr->size(); ++i) {
        if (!(*sieve_ptr)[i]) {
            const auto value = value_from_index(i);
            result.push_back(value);
            bool osc = i % 2;
            if (i < sqrt_limit) {
                for (unsigned long multiple = std::pow(value, 2);
                     multiple < limit;
                     multiple += (value * 2) * (osc ? 1 : 2)) {
                    osc = !osc;
                    (*sieve_ptr)[index_from_value(multiple)] = true;
                }
            }
        }
    }
    return result;
}

}  // namespace utility
#endif  // UTILITY_PRIMES_HPP
