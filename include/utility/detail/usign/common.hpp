#ifndef UTILITY_DETAIL_USIGN_COMMON_HPP
#define UTILITY_DETAIL_USIGN_COMMON_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <string>

namespace utility::detail::usign {

/// Converts ['0' - 'z'] to corresponding int, case insensitive
inline auto char_to_int(char c) -> int
{
    auto result = std::toupper(c) - static_cast<int>('0');
    if (result > 9)
        result -= 7;  // distance from '9' to 'A'
    return result;
}

/// Converts an int to a corresponding char, ['0' - 'Z'], returns uppercase
inline auto int_to_char(int i) -> char
{
    auto result = i + static_cast<int>('0');
    if (result > '9')
        result += 7;  // distance from '9' to 'A'
    return static_cast<char>(result);
}

/// Checks if value stored in string is odd, works for any base.
inline auto is_odd(std::string const& value) -> bool
{
    if (value.empty())
        return false;
    auto const last_digit = char_to_int(value.back());
    return (last_digit % 2) == 1;
}

/// Finds the most significant bit index of the bitset.
template <std::size_t N>
auto msb(std::bitset<N> const& bs) -> std::size_t
{
    for (auto i = N - 1; i < N; --i) {
        if (bs[i])
            return i;
    }
    return 0;
}

}  // namespace utility::detail::usign
#endif  // UTILITY_DETAIL_USIGN_COMMON_HPP
