#ifndef UTILITY_PRIMES_HPP
#define UTILITY_PRIMES_HPP
#include <bitset>
#include <vector>

namespace utility {

/// Generates list of all primes up to \p limit.
/** Created using Sieve of Eratosthenes. */
template <int limit>
auto generate_primes() {
    auto sieve = std::bitset<limit>{};
    sieve.flip();
    auto result = std::vector<int>{};
    // should only have to iterate through half? because i * j?
    for (auto i = 2; i < limit; ++i) {
        if (sieve[i]) {
            for (auto j = i + i; j < limit; j += i) {
                sieve[j] = false;
            }
            result.push_back(i);
        }
    }
    return result;
}

}  // namespace utility
#endif  // UTILITY_PRIMES_HPP
