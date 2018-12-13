#ifndef UTILITY_COMPOUND_TRAIT_HPP
#define UTILITY_COMPOUND_TRAIT_HPP
#include "detail/conjunction.hpp"

namespace utility {

/// Combines any number of traits to provide a static `type` member which acts
/// as a single trait with a `value` member which is true if all traits are true
/// for the given type.
template <template <typename> typename... Traits>
struct Compound_trait {
    template <typename T>
    using type = detail::Conjunction<Traits<T>...>;
};

}  // namespace utility
#endif  // UTILITY_COMPOUND_TRAIT_HPP
