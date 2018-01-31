/// ONLY INCLUDE ONE OF THE NEW OVERLOAD HEADERS ONCE IN ENTIRE PROGRAM.
#ifndef UTILITY_CLOG_NEW_HPP
#define UTILITY_CLOG_NEW_HPP
#include <iostream>

std::ostream& stream{std::clog};

#include "detail/new_overloads.hpp"

#endif  // UTILITY_CLOG_NEW_HPP
