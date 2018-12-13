#ifndef UTILITY_THOUSANDS_SEPERATOR_HPP
#define UTILITY_THOUSANDS_SEPERATOR_HPP
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

/// Insert locale specific thousands seperators into `value`. Returns a string.
/** Requires C++17 */
template <typename T>
std::string thousands_seperator(T value) {
    auto ss = std::stringstream{};
    ss.imbue(std::locale{""});
    ss << std::fixed;
    if constexpr (detail::is_string_type_v<T>) {
        auto value_str = std::string{value};
        if (value_str.find('.') != std::string::npos) {
            ss << std::stold(value_str);
        } else {
            ss << std::stoll(value_str);
        }
    } else {
        ss << value;
    }
    return ss.str();
}

}  // namespace utility
#endif  // UTILITY_THOUSANDS_SEPERATOR_HPP
