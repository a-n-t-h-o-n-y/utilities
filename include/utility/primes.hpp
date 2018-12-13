#ifndef UTILITY_PRIMES_HPP
#define UTILITY_PRIMES_HPP
#include <bitset>
#include <memory>
#include <vector>

namespace utility {

/// Generates a list of all primes up to, but not including, \p limit.
/** Sieve of Eratosthenes. */
template <int limit>
std::vector<int> generate_primes() {
    auto sieve_ptr = std::make_unique<std::bitset<limit>>();
    auto result = std::vector<int>{};
    for (auto i = 2uL; i < limit; ++i) {
        if (!(*sieve_ptr)[i]) {
            result.push_back(i);
            for (auto j = i + i; j < limit; j += i) {
                (*sieve_ptr)[j] = true;
            }
        }
    }
    return result;
}

}  // namespace utility
#endif  // UTILITY_PRIMES_HPP
