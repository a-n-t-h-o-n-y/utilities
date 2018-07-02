#ifndef UTILITY_DURATION_VIEW_HPP
#define UTILITY_DURATION_VIEW_HPP
#include <chrono>
#include <sstream>
#include <string>

#include <utility/thousands_seperator.hpp>

#include "detail/time_unit_string.hpp"
#include "detail/under_digit_limit.hpp"

namespace utility {

/// Format a std::chrono::duration object to a string of a specified time unit.
/// Requires C++17
template <typename Time_unit, typename Duration>
std::string duration_view(const Duration& duration,
                          bool thousands_seperator = true) {
    std::stringstream ss;
    auto ticks = std::chrono::duration_cast<Time_unit>(duration).count();
    std::string ticks_str{std::to_string(ticks)};
    if (thousands_seperator) {
        ticks_str = utility::thousands_seperator(ticks_str);
    }
    ss << ticks_str;
    std::string unit_name{detail::time_unit_string<Time_unit>()};
    if (unit_name.empty()) {
        ss << " ticks";
    } else {
        ss << ' ' << unit_name;
    }
    std::string result{ss.str()};
    if (ticks == 1 && !result.empty()) {
        result.pop_back();
    }
    return result;
}

/// Duration view that picks a Time_unit based on a limit of digits to output.
template <typename Duration>
std::string duration_view(const Duration& duration,
                          int digit_limit,
                          bool thousands_seperator = true) {
    using namespace std::chrono;
    using detail::under_digit_limit;
    if (under_digit_limit<nanoseconds>(duration, digit_limit)) {
        return duration_view<nanoseconds>(duration, thousands_seperator);
    } else if (under_digit_limit<microseconds>(duration, digit_limit)) {
        return duration_view<microseconds>(duration, thousands_seperator);
    } else if (under_digit_limit<milliseconds>(duration, digit_limit)) {
        return duration_view<milliseconds>(duration, thousands_seperator);
    } else if (under_digit_limit<seconds>(duration, digit_limit)) {
        return duration_view<seconds>(duration, thousands_seperator);
    } else if (under_digit_limit<minutes>(duration, digit_limit)) {
        return duration_view<minutes>(duration, thousands_seperator);
    } else {
        return duration_view<hours>(duration, thousands_seperator);
    }
}

}  // namespace utility
#endif  // UTILITY_DURATION_VIEW_HPP
