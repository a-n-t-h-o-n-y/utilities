#ifndef UTILITY_DETAIL_USIGN_BITSET_TO_STRING_HPP
#define UTILITY_DETAIL_USIGN_BITSET_TO_STRING_HPP
#include <bitset>
#include <cstddef>
#include <iterator>
#include <string>

#include "common.hpp"

namespace utility {
namespace detail {
namespace usign {

std::string add_strings_as(const std::string& v1,
                           const std::string& v2,
                           int base) {
    const std::string& shorter{v1.size() >= v2.size() ? v2 : v1};
    const std::string& longer{&shorter == &v1 ? v2 : v1};
    std::string result;
    int carry_over{0};
    auto long_iter = std::rbegin(longer);
    for (auto short_iter = std::rbegin(shorter);
         short_iter != std::rend(shorter); ++short_iter, ++long_iter) {
        int digit{char_to_int(*short_iter) + char_to_int(*long_iter) +
                  carry_over};
        result.insert(std::begin(result), int_to_char(digit % base));
        carry_over = static_cast<int>(digit >= base);
    }
    for (; long_iter != std::rend(longer); ++long_iter) {
        int digit{char_to_int(*long_iter) + carry_over};
        result.insert(std::begin(result), int_to_char(digit % base));
        carry_over = static_cast<int>(digit >= base);
    }
    if (carry_over != 0) {
        result.insert(std::begin(result), int_to_char(carry_over));
    }
    if (result.empty()) {
        result = "0";
    }
    return result;
}

std::string double_string_as(const std::string& value, int base) {
    if (value.empty()) {
        return "0";
    }
    std::string result;
    int carry_over{0};
    for (auto iter{std::rbegin(value)}; iter != std::rend(value); ++iter) {
        int digit{char_to_int(*iter) * 2 + carry_over};
        result.insert(std::begin(result), int_to_char(digit % base));
        carry_over = static_cast<int>(digit >= base);
    }
    if (carry_over != 0) {
        result.insert(std::begin(result), int_to_char(carry_over));
    }
    return result;
}

/// Translates binary value to a string containing value in base representation.
template <std::size_t N>
std::string bitset_to_string(std::bitset<N> data, int base) {
    std::string result{"0"};
    std::string place_value{"1"};
    for (std::size_t i{0}; i < data.size(); ++i) {
        if (data[i] == true) {
            result = add_strings_as(result, place_value, base);
        }
        place_value = double_string_as(place_value, base);
    }
    return result;
}

}  // namespace usign
}  // namespace detail
}  // namespace utility

#endif  // UTILITY_DETAIL_USIGN_BITSET_TO_STRING_HPP
