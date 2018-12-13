#ifndef UTILITY_TRAIT_DISJUNCTION_HPP
#define UTILITY_TRAIT_DISJUNCTION_HPP
#include <type_traits>

namespace utility {

/// Type trait to check a trait against multiple types
/** Providing a static `value` member if at least one type is true to the trait.
 *  Logical OR. Requires C++17. */
template <template <typename> typename Trait,
          typename Type,
          typename... Trailing_types>
struct Trait_disjunction
    : std::disjunction<Trait<Type>,
                       Trait_disjunction<Trait, Trailing_types...>> {};

template <template <typename> typename Trait, typename Type>
struct Trait_disjunction<Trait, Type> : Trait<Type> {};

/// Helper variable template providing `value`.
template <template <typename> typename Trait, typename... Types>
inline constexpr bool trait_disjunction_v =
    Trait_disjunction<Trait, Types...>::value;

}  // namespace utility
#endif  // UTILITY_TRAIT_DISJUNCTION_HPP
