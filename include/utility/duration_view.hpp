#ifndef UTILITY_DURATION_VIEW_HPP
#define UTILITY_DURATION_VIEW_HPP
#include <chrono>
#include <sstream>
#include <string>

#include <utility/digit_separator.hpp>

#include "detail/time_unit_string.hpp"
#include "detail/under_digit_limit.hpp"

namespace utility {

/// Format a std::chrono::duration object to a string of a specified time unit.
/** Requires C++17 */
template <typename Time_unit, typename Duration>
auto duration_view(Duration const& duration, bool digit_separator = true)
    -> std::string
{
    auto const ticks = std::chrono::duration_cast<Time_unit>(duration).count();
    auto ticks_str   = std::to_string(ticks);
    if (digit_separator)
        ticks_str = utility::digit_separator(ticks_str);
    auto ss = std::stringstream{};
    ss << ticks_str;

    if (auto const unit_name = detail::time_unit_string<Time_unit>();
        unit_name.empty()) {
        ss << " ticks";
    }
    else
        ss << ' ' << unit_name;

    auto result = ss.str();
    if (ticks == 1 && !result.empty())
        result.pop_back();
    return result;
}

/// Duration view that picks a Time_unit based on a limit of digits to output.
template <typename Duration>
auto duration_view(Duration const& duration,
                   int digit_limit,
                   bool digit_separator = true) -> std::string
{
    using namespace std::chrono;
    using detail::is_under_digit_limit;
    if (is_under_digit_limit<nanoseconds>(duration, digit_limit))
        return duration_view<nanoseconds>(duration, digit_separator);
    else if (is_under_digit_limit<microseconds>(duration, digit_limit))
        return duration_view<microseconds>(duration, digit_separator);
    else if (is_under_digit_limit<milliseconds>(duration, digit_limit))
        return duration_view<milliseconds>(duration, digit_separator);
    else if (is_under_digit_limit<seconds>(duration, digit_limit))
        return duration_view<seconds>(duration, digit_separator);
    else if (is_under_digit_limit<minutes>(duration, digit_limit))
        return duration_view<minutes>(duration, digit_separator);
    else
        return duration_view<hours>(duration, digit_separator);
}

}  // namespace utility
#endif  // UTILITY_DURATION_VIEW_HPP
