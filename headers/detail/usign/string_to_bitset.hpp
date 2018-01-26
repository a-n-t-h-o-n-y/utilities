#ifndef UTILITY_DETAIL_USIGN_STRING_TO_BITSET_HPP
#define UTILITY_DETAIL_USIGN_STRING_TO_BITSET_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <iterator>
#include <string>

#include "common.hpp"

namespace utility {
namespace detail {
namespace usign {

std::string divide_by_two(const std::string& value, int base) {
    if (value.empty()) {
        return value;
    }
    std::string result;
    int digit{0};
    const int kDivisor{2};
    for (char c : value) {
        digit += char_to_int(c);
        result.push_back(int_to_char(digit / kDivisor));
        digit = (digit % kDivisor) * base;
    }
    if (result.front() == '0' && result.size() > 1) {
        result.erase(std::begin(result));
    }
    return result;
}

template <std::size_t N>
std::bitset<N> any_base_to_binary(std::string value, int base) {
    if (value.empty()) {
        return std::bitset<N>{0};
    }
    std::bitset<N> result;
    for (std::size_t i{0}; i < N && value != "0"; ++i) {
        bool digit{is_odd(value)};
        result[i] = digit;
        value = divide_by_two(value, base);
    }
    return result;
}

// Convert string from Dec, Hex, Oct, or Binary representation to Binary bitset.
template <std::size_t N>
std::bitset<N> string_to_bitset(std::string value) {
    if (value.empty()) {
        return std::bitset<N>{0};
    }
    int base{10};
    if (value[0] == '0' && value.size() > 1) {
        // BINARY
        if (std::tolower(value[1]) == 'b') {
            std::string bits{std::begin(value) + 2, std::end(value)};
            return std::bitset<N>{bits};
        }
        // HEX
        if (std::tolower(value[1]) == 'x') {
            value.erase(std::begin(value), std::begin(value) + 2);
            base = 16;
        } else {  // OCT
            value.erase(std::begin(value));
            base = 8;
        }
    }
    return any_base_to_binary<N>(value, base);
}

}  // namespace usign
}  // namespace detail
}  // namespace utility

#endif  // UTILITY_DETAIL_USIGN_STRING_TO_BITSET_HPP
