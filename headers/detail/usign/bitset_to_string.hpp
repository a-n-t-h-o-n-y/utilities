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
    bool carry_over{false};
    std::size_t li{longer.size() - 1};
    for (std::size_t i{shorter.size() - 1}; i < shorter.size(); --i, --li) {
        int digit{char_to_int(shorter[i]) + char_to_int(longer[li]) +
                  carry_over};
        shorter[i] = int_to_char(digit % base);
        carry_over = digit >= base;
    }
    // longer is added to zeros, or carry_over
    for (; li < longer.size(); --li) {
        int digit{char_to_int(longer[li]) + carry_over};
        shorter.insert(std::begin(shorter), int_to_char(digit % base));
        carry_over = digit >= base;
    }
    if (carry_over) {
        shorter.insert(std::begin(shorter), int_to_char(carry_over));
    }
}

inline void inplace_double_as(std::string& value, int base) {
    bool carry_over{false};
    for (std::size_t i{value.size() - 1}; i < value.size(); --i) {
        int digit{char_to_int(value[i]) * 2 + carry_over};
        value[i] = int_to_char(digit % base);
        carry_over = digit >= base;
    }
    if (carry_over != 0) {
        value.insert(std::begin(value), int_to_char(carry_over));
    }
}

template <std::size_t N>
std::string bitset_to_string(std::bitset<N> data, int base) {
    std::string result{"0"};
    result.reserve(N);
    std::string place_value{"1"};
    place_value.reserve(N);
    for (std::size_t i{0}; i < N; ++i) {
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
