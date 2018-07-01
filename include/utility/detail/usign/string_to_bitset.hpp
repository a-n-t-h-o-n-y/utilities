#ifndef UTILITY_DETAIL_USIGN_STRING_TO_BITSET_HPP
#define UTILITY_DETAIL_USIGN_STRING_TO_BITSET_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <string>

#include "common.hpp"

namespace utility {
namespace detail {
namespace usign {

void inplace_half(std::string& value, int base) {
    int digit{0};
    const int kDivisor{2};
    for (std::size_t i{0}; i < value.size(); ++i) {
        digit += char_to_int(value[i]);
        value[i] = int_to_char(digit / kDivisor);
        digit = (digit % kDivisor) * base;
    }
    if (value.size() > 1 && value.front() == '0') {
        value.erase(0, 1);
    }
}

template <std::size_t N>
std::bitset<N> any_base_to_binary(std::string& value, int base) {
    std::bitset<N> result;
    for (std::size_t i{0}; i < N && value != "0"; ++i) {
        bool digit{is_odd(value)};
        result[i] = digit;
        inplace_half(value, base);
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
            value.erase(0, 2);
            return std::bitset<N>{value};
        }
        // HEX
        if (std::tolower(value[1]) == 'x') {
            value.erase(0, 2);
            base = 16;
        } else {  // OCT
            value.erase(0, 1);
            base = 8;
        }
    }
    return any_base_to_binary<N>(value, base);
}

}  // namespace usign
}  // namespace detail
}  // namespace utility

#endif  // UTILITY_DETAIL_USIGN_STRING_TO_BITSET_HPP
