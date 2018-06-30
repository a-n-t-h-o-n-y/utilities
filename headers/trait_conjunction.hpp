#ifndef UTILITY_TRAIT_CONJUNCTION_HPP
#define UTILITY_TRAIT_CONJUNCTION_HPP
#include <type_traits>

namespace utility {

/// Type trait to check a trait against multiple types, providing a static
/// `value` member if each type is true to the trait. Logical AND.
/// Requires C++17.
template <template <typename> typename Trait,
          typename Type,
          typename... Trailing_types>
struct Trait_conjunction
    : std::conjunction<Trait<Type>,
                       Trait_conjunction<Trait, Trailing_types...>> {};

template <template <typename> typename Trait, typename Type>
struct Trait_conjunction<Trait, Type> : Trait<Type> {};

/// Helper variable template providing `value`.
template <template <typename> typename Trait, typename... Types>
inline constexpr bool trait_conjunction_v =
    Trait_conjunction<Trait, Types...>::value;

}  // namespace utility
#endif  // UTILITY_TRAIT_CONJUNCTION_HPP
