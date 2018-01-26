#ifndef UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
#define UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
#include <bitset>
#include <cstddef>

#include "bit_comparisons.hpp"

namespace utility {
namespace detail {
namespace usign {

// ADDITION
template <std::size_t N>
std::bitset<N> bit_addition(const std::bitset<N>& lhs,
                            const std::bitset<N>& rhs) {
    std::bitset<N> result;
    bool carry_over{false};
    for (std::size_t i{0}; i < N; ++i) {
        int sum{carry_over + lhs[i] + rhs[i]};
        result[i] = (sum % 2) == 1;
        carry_over = sum > 1;
    }
    return result;
}

// SUBTRACTION
template <std::size_t N>
std::bitset<N> bit_subtraction(std::bitset<N> lhs, const std::bitset<N>& rhs) {
    for (std::size_t i{0}; i < lhs.size(); ++i) {
        lhs[i] = lhs[i] != rhs[i];
        if (lhs[i] && rhs[i]) {
            for (std::size_t j{i + 1}; j < lhs.size(); ++j) {
                lhs.flip(j);
                if (!lhs[j]) {
                    break;
                }
            }
        }
    }
    return lhs;
}

// DIVISION
template <std::size_t N>
std::bitset<N> bit_division(const std::bitset<N>& num,
                            const std::bitset<N>& den) {
    if (den == std::bitset<N>(2)) {
        std::bitset<N> result{num};
        result >>= 1;
        return result;
    }
    std::bitset<N> quo{0};
    std::bitset<N> rem{0};
    for (std::size_t i{N - 1}; i < N; --i) {
        rem <<= 1;
        rem[0] = num[i];
        if (detail::usign::operator>=(rem, den)) {
            rem = bit_subtraction(rem, den);
            quo[i] = true;
        }
    }
    return quo;
}

// MODULO
template <std::size_t N>
std::bitset<N> bit_modulo(const std::bitset<N>& num,
                          const std::bitset<N>& den) {
    std::bitset<N> rem{0};
    for (std::size_t i{N - 1}; i < N; --i) {
        rem <<= 1;
        rem[0] = num[i];
        if (detail::usign::operator>=(rem, den)) {
            rem = bit_subtraction(rem, den);
        }
    }
    return rem;
}

// MULTIPLICATION
template <std::size_t N>
std::bitset<N> bit_multiplication(const std::bitset<N>& lhs,
                                  const std::bitset<N>& rhs) {
    std::bitset<N> product{0};
    for (std::size_t i{0}; i < N; ++i) {
        if (rhs[i]) {
            product = bit_addition(product, lhs << i);
        }
    }
    return product;
}

}  // namespace usign
}  // namespace detail
}  // namespace utility

#endif  // UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
