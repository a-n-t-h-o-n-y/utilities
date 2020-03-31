#ifndef UTILITY_DETAIL_TIME_UNIT_STRING_HPP
#define UTILITY_DETAIL_TIME_UNIT_STRING_HPP
#include <chrono>
#include <string>
#include <type_traits>

namespace utility {
namespace detail {

template <typename Time_unit>
auto time_unit_string() -> std::string
{
    if constexpr (std::is_same_v<Time_unit, std::chrono::nanoseconds>)
        return "nanoseconds";
    else if constexpr (std::is_same_v<Time_unit, std::chrono::microseconds>)
        return "microseconds";
    else if constexpr (std::is_same_v<Time_unit, std::chrono::milliseconds>)
        return "milliseconds";
    else if constexpr (std::is_same_v<Time_unit, std::chrono::seconds>)
        return "seconds";
    else if constexpr (std::is_same_v<Time_unit, std::chrono::minutes>)
        return "minutes";
    else if constexpr (std::is_same_v<Time_unit, std::chrono::hours>)
        return "hours";
    else  // Unsupported Time_unit Type.
        return "";
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_TIME_UNIT_STRING_HPP
