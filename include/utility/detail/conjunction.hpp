#ifndef UTILITY_DETAIL_CONJUNCTION_HPP
#define UTILITY_DETAIL_CONJUNCTION_HPP
#include <type_traits>

namespace utility {
namespace detail {

template <typename...>
struct Conjunction : std::true_type {};

template <typename B1>
struct Conjunction<B1> : B1 {};

template <typename B1, typename... Bn>
struct Conjunction<B1, Bn...>
    : std::conditional_t<bool(B1::value), Conjunction<Bn...>, B1>::type {};

template <typename... B>
inline constexpr bool Conjunction_v = Conjunction<B...>::value;

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_CONJUNCTION_HPP
