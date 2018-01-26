#ifndef UTILITY_INTEGER_HPP
#define UTILITY_INTEGER_HPP
#include "signed_integer.hpp"
#include "unsigned_integer.hpp"

#include <cstdint>

namespace utility {

template <std::size_t N>
using Integer = Signed_integer<N>;

}  // namespace utility
#endif  // UTILITY_INTEGER_HPP
