#ifndef UTILITY_UNSIGNED_INTEGER_HPP
#define UTILITY_UNSIGNED_INTEGER_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>

#include "detail/usign/arithmetic.hpp"
#include "detail/usign/bit_comparisons.hpp"
#include "detail/usign/bitset_to_string.hpp"
#include "detail/usign/string_to_bitset.hpp"

namespace utility {

/// Arbitrary Precision Integer Class
template <std::size_t N>
class Unsigned_integer {
   public:
    static const std::size_t precision{N};

    /// Default constructs with value 0.
    Unsigned_integer() = default;

    /// Construct from integral types.
    template <
        typename T,
        typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
    Unsigned_integer(const T& value)
        : data_{static_cast<unsigned long long>(value)} {}

    /// Construct from string, represented in dec, hex, oct, or binary.
    Unsigned_integer(const std::string& value)
        : data_{detail::usign::string_to_bitset<N>(value)} {}

    /// Construct from const char*, represented in dec, hex, oct, or binary.
    Unsigned_integer(const char* value)
        : data_{detail::usign::string_to_bitset<N>(value)} {}

    /// Construct from bitset
    Unsigned_integer(const std::bitset<N>& value) : data_{value} {};

    /// Construct from other sized Integer types.
    template <std::size_t N2>
    Unsigned_integer(const Unsigned_integer<N2>& other);

    /// Return value as string in representation determined by base.
    std::string to_string(int base = 10) const;

    // Arithmetic
    Unsigned_integer operator+(const Unsigned_integer& rhs) const;
    Unsigned_integer operator-(const Unsigned_integer& rhs) const;
    Unsigned_integer operator/(const Unsigned_integer& divisor) const;
    Unsigned_integer operator*(const Unsigned_integer& rhs) const;
    Unsigned_integer operator%(const Unsigned_integer& divisor) const;

    // Comparison Operators
    bool operator==(const Unsigned_integer& rhs) const;
    bool operator!=(const Unsigned_integer& rhs) const;
    bool operator<(const Unsigned_integer& rhs) const;
    bool operator<=(const Unsigned_integer& rhs) const;
    bool operator>(const Unsigned_integer& rhs) const;
    bool operator>=(const Unsigned_integer& rhs) const;

    // friend class template
    template <std::size_t N2>
    friend class Unsigned_integer;

   private:
    std::bitset<N> data_;
};

// INCREMENT / DECREMENT - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
Unsigned_integer<N>& operator++(Unsigned_integer<N>& i) {
    i = i + 1;
    return i;
}

template <std::size_t N>
Unsigned_integer<N> operator++(Unsigned_integer<N>& i, int) {
    Unsigned_integer<N> result{i};
    ++i;
    return result;
}

template <std::size_t N>
Unsigned_integer<N>& operator--(Unsigned_integer<N>& i) {
    i = i - 1;
    return i;
}

template <std::size_t N>
Unsigned_integer<N> operator--(Unsigned_integer<N>& i, int) {
    Unsigned_integer<N> result{i};
    --i;
    return result;
}

// COMPOUND ASSIGNMENT OPERATORS - - - - - - - - - - - - - - - - - - - - - - - -
// Addition
template <std::size_t N, typename T>
Unsigned_integer<N>& operator+=(Unsigned_integer<N>& lhs, const T& rhs) {
    lhs = lhs + Unsigned_integer<N>{rhs};
    return lhs;
}

// Subtraction
template <std::size_t N, typename T>
Unsigned_integer<N>& operator-=(Unsigned_integer<N>& lhs, const T& rhs) {
    lhs = lhs - Unsigned_integer<N>{rhs};
    return lhs;
}

// Division
template <std::size_t N, typename T>
Unsigned_integer<N>& operator/=(Unsigned_integer<N>& num, const T& den) {
    num = num / Unsigned_integer<N>{den};
    return num;
}

// Modulo
template <std::size_t N, typename T>
Unsigned_integer<N>& operator%=(Unsigned_integer<N>& num, const T& den) {
    num = num % Unsigned_integer<N>{den};
    return num;
}

// Multiplication
template <std::size_t N, typename T>
Unsigned_integer<N>& operator*=(Unsigned_integer<N>& lhs, const T& rhs) {
    lhs = lhs * Unsigned_integer<N>{rhs};
    return lhs;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// For external linkage - C++17 inline in class to get rid of this.
template <std::size_t N>
const std::size_t Unsigned_integer<N>::precision;

// Copy Constructor
template <std::size_t N>
template <std::size_t N2>
Unsigned_integer<N>::Unsigned_integer(const Unsigned_integer<N2>& other) {
    for (std::size_t i{0}; i < data_.size() && i < other.data_.size(); ++i) {
        data_[i] = other.data_[i];
    }
}

// to_string(base)
template <std::size_t N>
std::string Unsigned_integer<N>::to_string(int base) const {
    if (base == 2) {
        std::string result{data_.to_string()};
        std::size_t start_pos{result.find_first_not_of('0')};
        if (start_pos == std::string::npos) {
            return "0";
        }
        return result.substr(start_pos);
    }
    return detail::usign::bitset_to_string(data_, base);
}

// COMPARISON OPERATORS - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
bool Unsigned_integer<N>::operator==(const Unsigned_integer& rhs) const {
    return this->data_ == rhs.data_;
}

template <std::size_t N>
bool Unsigned_integer<N>::operator!=(const Unsigned_integer& rhs) const {
    return this->data_ != rhs.data_;
}
template <std::size_t N>
bool Unsigned_integer<N>::operator<(const Unsigned_integer& rhs) const {
    return detail::usign::operator<(this->data_, rhs.data_);
}

template <std::size_t N>
bool Unsigned_integer<N>::operator<=(const Unsigned_integer& rhs) const {
    return detail::usign::operator<=(this->data_, rhs.data_);
}

template <std::size_t N>
bool Unsigned_integer<N>::operator>(const Unsigned_integer& rhs) const {
    return detail::usign::operator>(this->data_, rhs.data_);
}

template <std::size_t N>
bool Unsigned_integer<N>::operator>=(const Unsigned_integer& rhs) const {
    return detail::usign::operator>=(this->data_, rhs.data_);
}

// FORWARDING COMPARISON OPERATORS - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
bool operator==(std::uint64_t lhs, const Unsigned_integer<N>& rhs) {
    return rhs == lhs;
}

template <std::size_t N>
bool operator==(const std::string& lhs, const Unsigned_integer<N>& rhs) {
    return rhs == lhs;
}

template <std::size_t N>
bool operator!=(std::uint64_t lhs, const Unsigned_integer<N>& rhs) {
    return !(lhs == rhs);
}

template <std::size_t N>
bool operator!=(const std::string lhs, const Unsigned_integer<N>& rhs) {
    return !(lhs == rhs);
}

template <std::size_t N>
bool operator<(std::uint64_t lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} < rhs;
}

template <std::size_t N>
bool operator<(const std::string lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} < rhs;
}

template <std::size_t N>
bool operator<=(std::uint64_t lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} <= rhs;
}

template <std::size_t N>
bool operator<=(const std::string lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} <= rhs;
}

template <std::size_t N>
bool operator>(std::uint64_t lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} > rhs;
}

template <std::size_t N>
bool operator>(const std::string lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} > rhs;
}

template <std::size_t N>
bool operator>=(std::uint64_t lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} >= rhs;
}

template <std::size_t N>
bool operator>=(const std::string lhs, const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} >= rhs;
}

// ARITHMETIC - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Addition
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator+(
    const Unsigned_integer& rhs) const {
    std::bitset<N> result{detail::usign::bit_addition(data_, rhs.data_)};
    return Unsigned_integer{result};
}

// Subtraction
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator-(
    const Unsigned_integer& rhs) const {
    std::bitset<N> result{detail::usign::bit_subtraction(data_, rhs.data_)};
    return Unsigned_integer{result};
}

// Division
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator/(
    const Unsigned_integer& divisor) const {
    if (N == 0 || divisor == 0) {
        return 0;
    }
    if (divisor == 1) {
        return *this;
    }
    std::bitset<N> result{
        detail::usign::bit_division(this->data_, divisor.data_)};
    return Unsigned_integer<N>{result};
}

// Modulo
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator%(
    const Unsigned_integer& divisor) const {
    if (N == 0 || divisor == 0 || divisor == 1) {
        return 0;
    }
    std::bitset<N> result{
        detail::usign::bit_modulo(this->data_, divisor.data_)};
    return Unsigned_integer<N>{result};
}

// Multiplication
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator*(
    const Unsigned_integer& rhs) const {
    std::bitset<N> result{
        detail::usign::bit_multiplication(this->data_, rhs.data_)};
    return Unsigned_integer<N>{result};
}

// FORWARDING ARITHMETIC - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Addition
template <std::size_t N>
Unsigned_integer<N> operator+(std::uint64_t lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs + lhs;
}

template <std::size_t N>
Unsigned_integer<N> operator+(const std::string& lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs + lhs;
}

// Subtraction
template <std::size_t N>
Unsigned_integer<N> operator-(std::uint64_t lhs,
                              const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} - rhs;
}

template <std::size_t N>
Unsigned_integer<N> operator-(const std::string& lhs,
                              const Unsigned_integer<N>& rhs) {
    return Unsigned_integer<N>{lhs} - rhs;
}

// Division
template <std::size_t N>
Unsigned_integer<N> operator/(std::uint64_t num,
                              const Unsigned_integer<N>& den) {
    return Unsigned_integer<N>{num} / den;
}

template <std::size_t N>
Unsigned_integer<N> operator/(const std::string& num,
                              const Unsigned_integer<N>& den) {
    return Unsigned_integer<N>{num} / den;
}

// Modulo
template <std::size_t N>
Unsigned_integer<N> operator%(std::uint64_t num,
                              const Unsigned_integer<N>& den) {
    return Unsigned_integer<N>{num} % den;
}

template <std::size_t N>
Unsigned_integer<N> operator%(const std::string& num,
                              const Unsigned_integer<N>& den) {
    return Unsigned_integer<N>{num} % den;
}

// Multiplication
template <std::size_t N>
Unsigned_integer<N> operator*(std::uint64_t lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs * lhs;
}

template <std::size_t N>
Unsigned_integer<N> operator*(const std::string& lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs * lhs;
}

}  // namespace utility
#endif  // UTILITY_UNSIGNED_INTEGER_HPP
