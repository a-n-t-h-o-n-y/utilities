#ifndef UTILITY_MEMORY_VIEW_HPP
#define UTILITY_MEMORY_VIEW_HPP
#include <string>

#include "detail/memory_view/as_base.hpp"
#include "detail/memory_view/representation.hpp"

namespace utility {
using detail::memory_view::as_base;
using detail::memory_view::Representation;

/// Returns the binary representation of the given object's raw data as a
/// string. Space inserted every 4 digits(nibble) if separators set to true.
template <typename T>
std::string as_binary(const T& value, bool separators = true) {
    return as_base<Representation::Binary>(value, separators);
}

/// Returns the hexadecimal representation of the given object's raw data as a
/// string. Space inserted every 2 digits(byte) if separators set to true.
template <typename T>
std::string as_hex(const T& value, bool separators = true) {
    return as_base<Representation::Hex>(value, separators);
}

/// Returns the decimal representation of the given object's raw data as a
/// string. Comma inserted every 3 digits if separators set to true.
template <typename T>
std::string as_decimal(const T& value, bool separators = true) {
    return as_base<Representation::Decimal>(value, separators);
}

/// Returns the Octal representation of the given object's raw data as a
/// string. No separators availiable.
template <typename T>
std::string as_octal(const T& value) {
    return as_base<Representation::Octal>(value, false);
}

}  // namespace utility
#endif  // UTILITY_MEMORY_VIEW_HPP
