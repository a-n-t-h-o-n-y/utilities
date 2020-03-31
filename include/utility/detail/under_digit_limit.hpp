#ifndef UTILITY_DETAIL_UNDER_DIGIT_LIMIT_HPP
#define UTILITY_DETAIL_UNDER_DIGIT_LIMIT_HPP
#include <chrono>
#include <cmath>

namespace utility {
namespace detail {

template <typename Type_unit, typename Duration>
auto is_under_digit_limit(Duration const& duration, int limit) -> bool
{
    return std::chrono::duration_cast<Type_unit>(duration).count() <
           std::pow(10, limit);
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_UNDER_DIGIT_LIMIT_HPP
