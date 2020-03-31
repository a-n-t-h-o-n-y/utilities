#ifndef UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
#define UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
#include <algorithm>
#include <bitset>
#include <cstddef>

#include "bit_comparisons.hpp"
#include "common.hpp"

namespace utility::detail::usign {

// ADDITION
template <std::size_t N>
auto bit_addition(std::bitset<N> lhs, std::bitset<N> const& rhs)
    -> std::bitset<N>
{
    if (lhs == rhs)
        return lhs << 1;
    auto const limit = std::max(msb(lhs), msb(rhs)) + 1;
    auto carry_out   = false;
    for (auto i = std::size_t{0}; i < limit; ++i) {
        const auto sum = carry_out + lhs[i] + rhs[i];
        lhs[i]         = sum == 1 || sum == 3;
        carry_out      = sum > 1;
    }
    if (limit != N)
        lhs[limit] = carry_out + lhs[limit] + rhs[limit];
    return lhs;
}

// SUBTRACTION
template <std::size_t N>
auto bit_subtraction(std::bitset<N> lhs, std::bitset<N> const& rhs)
    -> std::bitset<N>
{
    for (auto i = 0uL; i < N; ++i) {
        lhs[i] = lhs[i] != rhs[i];
        if (lhs[i] && rhs[i]) {
            for (auto j = i + 1; j < N; ++j) {
                lhs.flip(j);
                if (!lhs[j])
                    break;
            }
        }
    }
    return lhs;
}

// DIVISION
template <std::size_t N>
auto bit_division(std::bitset<N> const& num, std::bitset<N> const& den)
    -> std::bitset<N>
{
    if (den == std::bitset<N>(2)) {
        auto result = std::bitset<N>{num};
        result >>= 1;
        return result;
    }
    auto quo = std::bitset<N>{0};
    auto rem = std::bitset<N>{0};
    for (auto i = N - 1; i < N; --i) {
        rem <<= 1;
        rem[0] = num[i];
        if (detail::usign::operator>=(rem, den)) {
            rem    = bit_subtraction(rem, den);
            quo[i] = true;
        }
    }
    return quo;
}

// MODULO
template <std::size_t N>
auto bit_modulo(std::bitset<N> const& num, std::bitset<N> const& den)
    -> std::bitset<N>
{
    auto rem = std::bitset<N>{0};
    for (auto i = N - 1; i < N; --i) {
        rem <<= 1;
        rem[0] = num[i];
        if (detail::usign::operator>=(rem, den))
            rem = bit_subtraction(rem, den);
    }
    return rem;
}

// MULTIPLICATION
template <std::size_t N>
auto bit_multiplication(std::bitset<N> const& lhs, std::bitset<N> const& rhs)
    -> std::bitset<N>
{
    auto product = std::bitset<N>{0};
    for (auto i = 0uL; i < N; ++i) {
        if (rhs[i])
            product = bit_addition(product, lhs << i);
    }
    return product;
}

// EXPONENTIATION
template <std::size_t N>
auto bit_exponentiation(std::bitset<N> const& base,
                        std::bitset<N> const& exponent) -> std::bitset<N>
{
    auto multiple = std::bitset<N>{base};
    auto result   = std::bitset<N>{1};
    auto limit    = 0uL;
    for (auto i = 0uL; i < N; ++i) {
        if (exponent[i])
            limit = i + 1;
    }
    for (auto i = 1uL; i < limit; ++i) {
        multiple = bit_multiplication(multiple, multiple);
        if (exponent[i])
            result = bit_multiplication(result, multiple);
    }
    if (exponent[0])
        result = bit_multiplication(result, base);
    return result;
}

// ROOT
template <std::size_t N>
auto bit_root(std::bitset<N> radicand, std::bitset<N> const& index)
    -> std::bitset<N>
{
    if (index.count() == 0)
        return std::bitset<N>{0};
    if (index.count() == 1 && index[0])
        return radicand;
    if (radicand.count() == 0)
        return std::bitset<N>{0};
    if (radicand.count() == 1 && radicand[0])
        return std::bitset<N>{1};
    auto result = std::bitset<N>{2};
    while (true) {
        auto test  = result;
        auto limit = bit_subtraction(index, std::bitset<N>{1});
        for (auto i = std::bitset<N>{0}; i < limit;
             i      = bit_addition(i, std::bitset<N>{1})) {
            test = bit_multiplication(test, result);
        }
        if (test > radicand)
            return bit_subtraction(result, std::bitset<N>{1});
        result = bit_addition(result, std::bitset<N>{1});
    }
}

}  // namespace utility::detail::usign

#endif  // UTILITY_DETAIL_USIGN_ARITHMETIC_HPP
