#ifndef UTILITY_DETAIL_IS_STD_ARRAY_HPP
#define UTILITY_DETAIL_IS_STD_ARRAY_HPP
#include <array>
#include <cstddef>
#include <type_traits>

namespace utility {
namespace detail {

template <typename>
struct is_std_array : std::false_type {};

template <typename T, std::size_t N>
struct is_std_array<std::array<T, N>> : std::true_type {};

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_IS_STD_ARRAY_HPP
