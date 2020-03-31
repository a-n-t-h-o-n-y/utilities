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
inline constexpr auto even(std::size_t index) -> bool { return index % 2 == 0; }

/// Returns value corresponding to \p index.
inline constexpr auto value_from_index(std::size_t index) -> int
{
    return 5 + (even(index) ? index * 3 : 3 * (index - 1) + 2);
}

/// Returns the index in the bitset corresponding to \p value.
inline constexpr auto index_from_value(int value) -> std::size_t
{
    return (value - 4) / 3;
}

/// Thirds a size for a container so that ...
inline constexpr auto third_size(std::size_t limit) -> std::size_t
{
    return (limit / 3) - 1;
}

// Calculates pi(x), the approximate number of primes up to \p limit.
inline constexpr auto approx_prime_count(int limit) -> std::size_t
{
    return limit / (std::log(limit) - 1);
}

}  // namespace detail

/// Generates a list of all primes up to, but not including, \p limit.
/** Uses Sieve of Eratosthenes with multiples of 2 and 3 removed. */
template <int limit>
auto generate_primes() -> std::vector<int>
{
    if constexpr (limit < 2)
        return {};
    else if constexpr (limit == 3)
        return {2};

    using namespace detail;
    auto const sieve_ptr  = std::make_unique<std::bitset<third_size(limit)>>();
    auto const sqrt_limit = std::size_t(std::sqrt(sieve_ptr->size()));
    auto result           = std::vector<int>{2, 3};
    result.reserve(approx_prime_count(limit));
    for (auto i = 0uL; i < sieve_ptr->size(); ++i) {
        if (!(*sieve_ptr)[i]) {
            auto const value = value_from_index(i);
            result.push_back(value);
            bool osc = i % 2;
            if (i < sqrt_limit) {
                for (unsigned long multiple = std::pow(value, 2);
                     multiple < limit;
                     multiple += (value * 2) * (osc ? 1 : 2)) {
                    (*sieve_ptr)[index_from_value(multiple)] = true;
                    osc                                      = !osc;
                }
            }
        }
    }
    return result;
}

}  // namespace utility
#endif  // UTILITY_PRIMES_HPP
