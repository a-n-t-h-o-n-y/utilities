#ifndef UTILITY_DETAIL_USIGN_COMMON_HPP
#define UTILITY_DETAIL_USIGN_COMMON_HPP
#include <cctype>
#include <string>

namespace utility {
namespace detail {
namespace usign {

/// Converts ['0' - 'z'] to corresponding int, case insensitive
int char_to_int(char c) {
    int result{std::toupper(c) - static_cast<int>('0')};
    if (result > 9) {
        result -= 7;  // distance from '9' to 'A'
    }
    return result;
}

/// Converts an int to a corresponding char, ['0' - 'Z'], returns uppercase
char int_to_char(int i) {
    int result{i + static_cast<int>('0')};
    if (result > '9') {
        result += 7;  // distance from '9' to 'A'
    }
    return static_cast<char>(result);
}

/// Checks if value stored in string is odd, works for any base.
bool is_odd(const std::string& value) {
    if (value.empty()) {
        return false;
    }
    int last_digit{char_to_int(value.back())};
    return (last_digit % 2) == 1;
}

}  // namespace usign
}  // namespace detail
}  // namespace utility

#endif  // UTILITY_DETAIL_USIGN_COMMON_HPP
