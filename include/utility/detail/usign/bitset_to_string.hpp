#ifndef UTILITY_DETAIL_USIGN_BITSET_TO_STRING_HPP
#define UTILITY_DETAIL_USIGN_BITSET_TO_STRING_HPP
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <iterator>
#include <string>

#include "common.hpp"

namespace utility {
namespace detail {
namespace usign {

inline void inplace_add_as(std::string& shorter,
                           const std::string& longer,
                           int base) {
    auto carry_out = false;
    auto li = longer.size() - 1;
    for (auto i = shorter.size() - 1; i < shorter.size(); --i, --li) {
        const auto digit =
            char_to_int(shorter[i]) + char_to_int(longer[li]) + carry_out;
        shorter[i] = int_to_char(digit % base);
        carry_out = digit >= base;
    }
    // longer is added to zeros, or carry_over
    for (; li < longer.size(); --li) {
        const auto digit = char_to_int(longer[li]) + carry_out;
        shorter.insert(std::begin(shorter), int_to_char(digit % base));
        carry_out = digit >= base;
    }
    if (carry_out) {
        shorter.insert(std::begin(shorter), int_to_char(carry_out));
    }
}

inline void inplace_double_as(std::string& value, int base) {
    auto carry_out = false;
    for (auto i = value.size() - 1; i < value.size(); --i) {
        const auto digit = char_to_int(value[i]) * 2 + carry_out;
        value[i] = int_to_char(digit % base);
        carry_out = digit >= base;
    }
    if (carry_out != 0) {
        value.insert(std::begin(value), int_to_char(carry_out));
    }
}

template <std::size_t N>
std::string bitset_to_string(std::bitset<N> data, int base) {
    auto result = std::string{"0"};
    result.reserve(N);
    auto place_value = std::string{"1"};
    place_value.reserve(N);
    for (auto i = std::size_t{0}; i < N; ++i) {
        if (data[i]) {
            inplace_add_as(result, place_value, base);
        }
        if (i + 1 < N) {
            inplace_double_as(place_value, base);
        }
    }
    return result;
}

}  // namespace usign
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_USIGN_BITSET_TO_STRING_HPP
