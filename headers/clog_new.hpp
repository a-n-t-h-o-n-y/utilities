/// ONLY INCLUDE ONE OF THE NEW OVERLOAD HEADERS ONCE IN ENTIRE PROGRAM.
#ifndef UTILITY_CLOG_NEW_HPP
#define UTILITY_CLOG_NEW_HPP
#include <iostream>

namespace utility {
namespace detail {

std::ostream& stream_{std::clog};

}  // namespace detail
}  // namespace utility

#include "detail/new_overloads.hpp"

#endif  // UTILITY_CLOG_NEW_HPP
