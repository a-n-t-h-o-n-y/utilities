#ifndef UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
#define UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
#include <bitset>
#include <cstddef>

#include "bit_comparisons.hpp"
#include "common.hpp"

namespace utility {
namespace detail {
namespace usign {

// ADDITION
template <std::size_t N>
std::bitset<N> bit_addition(std::bitset<N> lhs, const std::bitset<N>& rhs) {
    if (lhs == rhs) {
        return lhs << 1;
    }
    std::size_t lhs_msb{msb(lhs)};
    std::size_t rhs_msb{msb(rhs)};
    std::size_t limit{lhs_msb > rhs_msb ? lhs_msb : rhs_msb};
    ++limit;
    bool carry_over{false};
    for (std::size_t i{0}; i < limit; ++i) {
        int sum{carry_over + lhs[i] + rhs[i]};
        lhs[i] = sum == 1 || sum == 3;
        carry_over = sum > 1;
    }
    if (limit != N) {
        lhs[limit] = carry_over + lhs[limit] + rhs[limit];
    }
    return lhs;
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

// EXPONENTIATION
template <std::size_t N>
std::bitset<N> bit_exponentiation(const std::bitset<N>& base,
                                  const std::bitset<N>& exponent) {
    std::bitset<N> multiple{base};
    std::bitset<N> result{1};
    std::size_t limit{0};
    for (std::size_t i{0}; i < N; ++i) {
        if (exponent[i]) {
            limit = i + 1;
        }
    }
    for (std::size_t i{1}; i < limit; ++i) {
        multiple = bit_multiplication(multiple, multiple);
        if (exponent[i]) {
            result = bit_multiplication(result, multiple);
        }
    }
    if (exponent[0]) {
        result = bit_multiplication(result, base);
    }
    return result;
}

// ROOT
template <std::size_t N>
std::bitset<N> bit_root(std::bitset<N> radicand, const std::bitset<N>& index) {
    if (index.count() == 0) {
        return std::bitset<N>{0};
    }
    if (index.count() == 1 && index[0]) {
        return radicand;
    }
    if (radicand.count() == 0) {
        return std::bitset<N>{0};
    }
    if (radicand.count() == 1 && radicand[0]) {
        return std::bitset<N>{1};
    }
    std::bitset<N> result{2};
    while (true) {
        std::bitset<N> test{result};
        std::bitset<N> limit{bit_subtraction(index, std::bitset<N>{1})};
        for (std::bitset<N> i{0}; i < limit;
             i = bit_addition(i, std::bitset<N>{1})) {
            test = bit_multiplication(test, result);
        }
        if (test > radicand) {
            return bit_subtraction(result, std::bitset<N>{1});
        }
        result = bit_addition(result, std::bitset<N>{1});
    }
}

}  // namespace usign
}  // namespace detail
}  // namespace utility

#endif  // UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
