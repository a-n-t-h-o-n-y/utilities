#ifndef UTILITY_UNSIGNED_INTEGER_HPP
#define UTILITY_UNSIGNED_INTEGER_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
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
    Unsigned_integer(const std::bitset<N>& value) : data_{value} {}

    /// Construct from another Unsigned_integer<N>
    Unsigned_integer(const Unsigned_integer& other) : data_{other.data_} {}

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
    Unsigned_integer exp(const Unsigned_integer& exponent) const;
    Unsigned_integer root(const Unsigned_integer& index) const;

    // Comparison Operators
    bool operator==(const Unsigned_integer& rhs) const;
    bool operator!=(const Unsigned_integer& rhs) const;
    bool operator<(const Unsigned_integer& rhs) const;
    bool operator<=(const Unsigned_integer& rhs) const;
    bool operator>(const Unsigned_integer& rhs) const;
    bool operator>=(const Unsigned_integer& rhs) const;

    // Bit Operators
    Unsigned_integer operator&(const Unsigned_integer& rhs) const;
    Unsigned_integer operator|(const Unsigned_integer& rhs) const;
    Unsigned_integer operator^(const Unsigned_integer& rhs) const;
    Unsigned_integer operator~() const;
    Unsigned_integer operator<<(std::size_t pos) const;
    Unsigned_integer operator>>(std::size_t pos) const;

    // Compound Bit Operator Assignments
    Unsigned_integer& operator&=(const Unsigned_integer& other);
    Unsigned_integer& operator|=(const Unsigned_integer& other);
    Unsigned_integer& operator^=(const Unsigned_integer& other);
    Unsigned_integer& operator<<=(std::size_t pos);
    Unsigned_integer& operator>>=(std::size_t pos);

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
        const auto result = data_.to_string();
        const auto start_pos = result.find_first_not_of('0');
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

// BIT OPERATORS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// AND
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator&(
    const Unsigned_integer& rhs) const {
    return this->data_ & rhs.data_;
}

// OR
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator|(
    const Unsigned_integer& rhs) const {
    return this->data_ | rhs.data_;
}

// XOR
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator^(
    const Unsigned_integer& rhs) const {
    return this->data_ ^ rhs.data_;
}

// NOT
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator~() const {
    return ~this->data_;
}

// Shift Left
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator<<(std::size_t pos) const {
    return this->data_ << pos;
}

// Shift Right
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator>>(std::size_t pos) const {
    return this->data_ >> pos;
}

// FORWARDING BIT OPERATORS - - - - - - - - - - - - - - - - - - - - - - - -
// - - AND
template <std::size_t N>
Unsigned_integer<N> operator&(std::uint64_t lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs & lhs;
}

template <std::size_t N>
Unsigned_integer<N> operator&(const std::string& lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs & lhs;
}

// OR
template <std::size_t N>
Unsigned_integer<N> operator|(std::uint64_t lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs | lhs;
}

template <std::size_t N>
Unsigned_integer<N> operator|(const std::string& lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs | lhs;
}

// XOR
template <std::size_t N>
Unsigned_integer<N> operator^(std::uint64_t lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs ^ lhs;
}

template <std::size_t N>
Unsigned_integer<N> operator^(const std::string& lhs,
                              const Unsigned_integer<N>& rhs) {
    return rhs ^ lhs;
}

// COMPOUND BIT OPERATOR ASSIGNMENT - - - - - - - - - - - - - - - - - - - -
// - -
template <std::size_t N>
Unsigned_integer<N>& Unsigned_integer<N>::operator&=(
    const Unsigned_integer& other) {
    this->data_ &= other.data_;
    return *this;
}

template <std::size_t N>
Unsigned_integer<N>& Unsigned_integer<N>::operator|=(
    const Unsigned_integer& other) {
    this->data_ |= other.data_;
    return *this;
}

template <std::size_t N>
Unsigned_integer<N>& Unsigned_integer<N>::operator^=(
    const Unsigned_integer& other) {
    this->data_ ^= other.data_;
    return *this;
}

// Shift Left
template <std::size_t N>
Unsigned_integer<N>& Unsigned_integer<N>::operator<<=(std::size_t pos) {
    this->data_ <<= pos;
    return *this;
}

// Shift Right
template <std::size_t N>
Unsigned_integer<N>& Unsigned_integer<N>::operator>>=(std::size_t pos) {
    this->data_ >>= pos;
    return *this;
}

// ARITHMETIC - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Addition
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator+(
    const Unsigned_integer& rhs) const {
    return detail::usign::bit_addition(data_, rhs.data_);
}

// Subtraction
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator-(
    const Unsigned_integer& rhs) const {
    return detail::usign::bit_subtraction(data_, rhs.data_);
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
    return detail::usign::bit_division(this->data_, divisor.data_);
}

// Modulo
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator%(
    const Unsigned_integer& divisor) const {
    if (N == 0 || divisor == 0 || divisor == 1) {
        return 0;
    }
    return detail::usign::bit_modulo(this->data_, divisor.data_);
}

// Multiplication
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::operator*(
    const Unsigned_integer& rhs) const {
    return detail::usign::bit_multiplication(this->data_, rhs.data_);
}

// Exponentiation
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::exp(
    const Unsigned_integer& exponent) const {
    return detail::usign::bit_exponentiation(this->data_, exponent.data_);
}

// Root
template <std::size_t N>
Unsigned_integer<N> Unsigned_integer<N>::root(
    const Unsigned_integer& index) const {
    return detail::usign::bit_root(this->data_, index.data_);
}

// FORWARDING ARITHMETIC - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Addition
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

// IOSTREAMS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const Unsigned_integer<N>& value) {
    auto base = 10;
    auto flags = os.flags() & std::ios::basefield;
    if (flags == std::ios::hex) {
        base = 16;
    } else if (flags == std::ios::oct) {
        base = 8;
    }
    os << value.to_string(base);
    return os;
}

template <std::size_t N>
std::istream& operator>>(std::istream& is, Unsigned_integer<N>& value) {
    auto input = std::string{};
    if (is.good()) {
        is >> input;
    }
    value = Unsigned_integer<N>{input};
    return is;
}

}  // namespace utility
#endif  // UTILITY_UNSIGNED_INTEGER_HPP
