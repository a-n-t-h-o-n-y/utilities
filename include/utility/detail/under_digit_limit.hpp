#ifndef UTILITY_DETAIL_UNDER_DIGIT_LIMIT_HPP
#define UTILITY_DETAIL_UNDER_DIGIT_LIMIT_HPP
#include <chrono>
#include <cmath>

namespace utility {
namespace detail {

template <typename Type_unit, typename Duration>
bool is_under_digit_limit(const Duration& duration, int limit) {
    return std::chrono::duration_cast<Type_unit>(duration).count() <
           std::pow(10, limit);
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_UNDER_DIGIT_LIMIT_HPP
