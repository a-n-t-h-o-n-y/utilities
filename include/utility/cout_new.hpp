#ifndef UTILITY_COUT_NEW_HPP
#define UTILITY_COUT_NEW_HPP
#include <iostream>

namespace utility {
namespace detail {

// Only include one new overload header in the entire program.
inline std::ostream& stream_{std::cout};

}  // namespace detail
}  // namespace utility

#include "detail/new_overloads.hpp"

#endif  // UTILITY_COUT_NEW_HPP
