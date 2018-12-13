#ifndef UTILITY_DETAIL_USIGN_COMMON_HPP
#define UTILITY_DETAIL_USIGN_COMMON_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <string>

namespace utility {
namespace detail {
namespace usign {

/// Converts ['0' - 'z'] to corresponding int, case insensitive
inline int char_to_int(char c) {
    auto result = std::toupper(c) - static_cast<int>('0');
    if (result > 9) {
        result -= 7;  // distance from '9' to 'A'
    }
    return result;
}

/// Converts an int to a corresponding char, ['0' - 'Z'], returns uppercase
inline char int_to_char(int i) {
    auto result = i + static_cast<int>('0');
    if (result > '9') {
        result += 7;  // distance from '9' to 'A'
    }
    return static_cast<char>(result);
}

/// Checks if value stored in string is odd, works for any base.
inline bool is_odd(const std::string& value) {
    if (value.empty()) {
        return false;
    }
    const auto last_digit = char_to_int(value.back());
    return (last_digit % 2) == 1;
}

/// Finds the most significant bit index of the bitset.
template <std::size_t N>
std::size_t msb(const std::bitset<N>& bs) {
    for (auto i = N - 1; i < N; --i) {
        if (bs[i]) {
            return i;
        }
    }
    return 0;
}

}  // namespace usign
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_USIGN_COMMON_HPP
