#ifndef UTILITY_THOUSANDS_SEPARATOR_HPP
#define UTILITY_THOUSANDS_SEPARATOR_HPP
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <type_traits>

namespace utility {

namespace detail {
template <typename T>
inline constexpr bool is_string_type_v =
    std::disjunction_v<std::is_same<T, std::string>,
                       std::is_same<T, const char*>>;
}

/// Insert locale specific thousands separators into `value`. Returns a string.
/** Requires C++17 */
template <typename T>
auto digit_separator(T value, std::string locale_str = "en_US.UTF-8")
    -> std::string
{
    auto ss = std::ostringstream{};
    ss.imbue(std::locale{locale_str});
    ss << std::fixed;
    if constexpr (detail::is_string_type_v<T>) {
        if (auto const value_str = std::string{value};
            value_str.find('.') != std::string::npos) {
            ss << std::stold(value_str);
        }
        else
            ss << std::stoll(value_str);
    }
    else
        ss << value;
    return ss.str();
}

}  // namespace utility
#endif  // UTILITY_THOUSANDS_SEPARATOR_HPP
