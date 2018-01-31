/// ONLY INCLUDE ONE OF THE NEW OVERLOAD HEADERS ONCE IN ENTIRE PROGRAM.
#ifndef UTILITY_COUT_NEW_HPP
#define UTILITY_COUT_NEW_HPP
#include <iostream>

std::ostream& stream{std::cout};

#include "detail/new_overloads.hpp"

#endif  // UTILITY_COUT_NEW_HPP
