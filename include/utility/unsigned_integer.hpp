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
    static inline auto const precision = N;

    /// Default constructs with value 0.
    Unsigned_integer() = default;

    /// Construct from integral types.
    template <typename T,
              typename std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    Unsigned_integer(T const& value)
        : data_{static_cast<unsigned long long>(value)}
    {}

    /// Construct from string, represented in dec, hex, oct, or binary.
    Unsigned_integer(std::string const& value)
        : data_{detail::usign::string_to_bitset<N>(value)}
    {}

    /// Construct from char const*, represented in dec, hex, oct, or binary.
    Unsigned_integer(char const* value)
        : data_{detail::usign::string_to_bitset<N>(value)}
    {}

    /// Construct from bitset
    Unsigned_integer(std::bitset<N> const& value) : data_{value} {}

    /// Construct from another Unsigned_integer<N>
    Unsigned_integer(Unsigned_integer const& other) : data_{other.data_} {}

    /// Construct from other sized Integer types.
    template <std::size_t N2>
    Unsigned_integer(Unsigned_integer<N2> const& other)
    {
        for (auto i = 0uL; i < data_.size() && i < other.data_.size(); ++i)
            data_[i] = other.data_[i];
    }

    /// Return value as string in representation determined by base.
    auto to_string(int base = 10) const -> std::string
    {
        if (base != 2)
            return detail::usign::bitset_to_string(data_, base);
        auto const result    = data_.to_string();
        auto const start_pos = result.find_first_not_of('0');
        if (start_pos == std::string::npos)
            return "0";
        else
            return result.substr(start_pos);
    }

    // Arithmetic
    auto operator+(Unsigned_integer const& rhs) const -> Unsigned_integer
    {
        return detail::usign::bit_addition(data_, rhs.data_);
    }
    auto operator-(Unsigned_integer const& rhs) const -> Unsigned_integer
    {
        return detail::usign::bit_subtraction(data_, rhs.data_);
    }
    auto operator/(Unsigned_integer const& divisor) const -> Unsigned_integer
    {
        if (N == 0 || divisor == 0)
            return 0;
        if (divisor == 1)
            return *this;
        return detail::usign::bit_division(this->data_, divisor.data_);
    }
    auto operator*(Unsigned_integer const& rhs) const -> Unsigned_integer
    {
        return detail::usign::bit_multiplication(this->data_, rhs.data_);
    }
    auto operator%(Unsigned_integer const& divisor) const -> Unsigned_integer
    {
        if (N == 0 || divisor == 0 || divisor == 1)
            return 0;
        else
            return detail::usign::bit_modulo(this->data_, divisor.data_);
    }
    auto exp(Unsigned_integer const& exponent) const -> Unsigned_integer
    {
        return detail::usign::bit_exponentiation(this->data_, exponent.data_);
    }
    auto root(Unsigned_integer const& index) const -> Unsigned_integer
    {
        return detail::usign::bit_root(this->data_, index.data_);
    }

    // Comparison Operators
    auto operator==(Unsigned_integer const& rhs) const -> bool
    {
        return this->data_ == rhs.data_;
    }
    auto operator!=(Unsigned_integer const& rhs) const -> bool
    {
        return this->data_ != rhs.data_;
    }
    auto operator<(Unsigned_integer const& rhs) const -> bool
    {
        return detail::usign::operator<(this->data_, rhs.data_);
    }
    auto operator<=(Unsigned_integer const& rhs) const -> bool
    {
        return detail::usign::operator<=(this->data_, rhs.data_);
    }
    auto operator>(Unsigned_integer const& rhs) const -> bool
    {
        return detail::usign::operator>(this->data_, rhs.data_);
    }
    auto operator>=(Unsigned_integer const& rhs) const -> bool
    {
        return detail::usign::operator>=(this->data_, rhs.data_);
    }

    // Bit Operators
    auto operator&(Unsigned_integer const& rhs) const -> Unsigned_integer
    {
        return this->data_ & rhs.data_;
    }
    auto operator|(Unsigned_integer const& rhs) const -> Unsigned_integer
    {
        return this->data_ | rhs.data_;
    }
    auto operator^(Unsigned_integer const& rhs) const -> Unsigned_integer
    {
        return this->data_ ^ rhs.data_;
    }
    auto operator~() const -> Unsigned_integer { return ~(this->data_); }
    auto operator<<(std::size_t pos) const -> Unsigned_integer
    {
        return this->data_ << pos;
    }
    auto operator>>(std::size_t pos) const -> Unsigned_integer
    {
        return this->data_ >> pos;
    }

    // Compound Bit Operator Assignments
    auto operator&=(Unsigned_integer const& other) -> Unsigned_integer&
    {
        this->data_ &= other.data_;
        return *this;
    }
    auto operator|=(Unsigned_integer const& other) -> Unsigned_integer&
    {
        this->data_ |= other.data_;
        return *this;
    }
    auto operator^=(Unsigned_integer const& other) -> Unsigned_integer&
    {
        this->data_ ^= other.data_;
        return *this;
    }
    auto operator<<=(std::size_t pos) -> Unsigned_integer&
    {
        this->data_ <<= pos;
        return *this;
    }
    auto operator>>=(std::size_t pos) -> Unsigned_integer&
    {
        this->data_ >>= pos;
        return *this;
    }

    // friend class template
    template <std::size_t N2>
    friend class Unsigned_integer;

   private:
    std::bitset<N> data_;
};

// INCREMENT / DECREMENT - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
auto operator++(Unsigned_integer<N>& i) -> Unsigned_integer<N>&
{
    i = i + 1;
    return i;
}

template <std::size_t N>
auto operator++(Unsigned_integer<N>& i, int) -> Unsigned_integer<N>
{
    auto result = Unsigned_integer<N>{i};
    ++i;
    return result;
}

template <std::size_t N>
auto operator--(Unsigned_integer<N>& i) -> Unsigned_integer<N>&
{
    i = i - 1;
    return i;
}

template <std::size_t N>
auto operator--(Unsigned_integer<N>& i, int) -> Unsigned_integer<N>
{
    auto result = Unsigned_integer<N>{i};
    --i;
    return result;
}

// COMPOUND ASSIGNMENT OPERATORS - - - - - - - - - - - - - - - - - - - - - - - -
// Addition
template <std::size_t N, typename T>
auto operator+=(Unsigned_integer<N>& lhs, const T& rhs) -> Unsigned_integer<N>&
{
    lhs = lhs + Unsigned_integer<N>{rhs};
    return lhs;
}

// Subtraction
template <std::size_t N, typename T>
auto operator-=(Unsigned_integer<N>& lhs, const T& rhs) -> Unsigned_integer<N>&
{
    lhs = lhs - Unsigned_integer<N>{rhs};
    return lhs;
}

// Division
template <std::size_t N, typename T>
auto operator/=(Unsigned_integer<N>& num, const T& den) -> Unsigned_integer<N>&
{
    num = num / Unsigned_integer<N>{den};
    return num;
}

// Modulo
template <std::size_t N, typename T>
auto operator%=(Unsigned_integer<N>& num, const T& den) -> Unsigned_integer<N>&
{
    num = num % Unsigned_integer<N>{den};
    return num;
}

// Multiplication
template <std::size_t N, typename T>
auto operator*=(Unsigned_integer<N>& lhs, const T& rhs) -> Unsigned_integer<N>&
{
    lhs = lhs * Unsigned_integer<N>{rhs};
    return lhs;
}

// FORWARDING COMPARISON OPERATORS - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
auto operator==(std::uint64_t lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return rhs == lhs;
}

template <std::size_t N>
auto operator==(std::string const& lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return rhs == lhs;
}

template <std::size_t N>
auto operator!=(std::uint64_t lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return !(lhs == rhs);
}

template <std::size_t N>
auto operator!=(std::string const& lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return !(lhs == rhs);
}

template <std::size_t N>
auto operator<(std::uint64_t lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} < rhs;
}

template <std::size_t N>
auto operator<(std::string const& lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} < rhs;
}

template <std::size_t N>
auto operator<=(std::uint64_t lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} <= rhs;
}

template <std::size_t N>
auto operator<=(std::string const& lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} <= rhs;
}

template <std::size_t N>
auto operator>(std::uint64_t lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} > rhs;
}

template <std::size_t N>
auto operator>(std::string const& lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} > rhs;
}

template <std::size_t N>
auto operator>=(std::uint64_t lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} >= rhs;
}

template <std::size_t N>
auto operator>=(std::string const& lhs, Unsigned_integer<N> const& rhs) -> bool
{
    return Unsigned_integer<N>{lhs} >= rhs;
}

// FORWARDING BIT OPERATORS - - - - - - - - - - - - - - - - - - - - - - - -
// - - AND
template <std::size_t N>
auto operator&(std::uint64_t lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs & lhs;
}

template <std::size_t N>
auto operator&(std::string const& lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs & lhs;
}

// OR
template <std::size_t N>
auto operator|(std::uint64_t lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs | lhs;
}

template <std::size_t N>
auto operator|(std::string const& lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs | lhs;
}

// XOR
template <std::size_t N>
auto operator^(std::uint64_t lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs ^ lhs;
}

template <std::size_t N>
auto operator^(std::string const& lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs ^ lhs;
}

// FORWARDING ARITHMETIC - - - - - - - - - - - - - - - - - - - - - - - - - -
// Addition
template <std::size_t N>
auto operator+(std::uint64_t lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs + lhs;
}

template <std::size_t N>
auto operator+(std::string const& lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs + lhs;
}

// Subtraction
template <std::size_t N>
auto operator-(std::uint64_t lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return Unsigned_integer<N>{lhs} - rhs;
}

template <std::size_t N>
auto operator-(std::string const& lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return Unsigned_integer<N>{lhs} - rhs;
}

// Division
template <std::size_t N>
auto operator/(std::uint64_t num, Unsigned_integer<N> const& den)
    -> Unsigned_integer<N>
{
    return Unsigned_integer<N>{num} / den;
}

template <std::size_t N>
auto operator/(std::string const& num, Unsigned_integer<N> const& den)
    -> Unsigned_integer<N>
{
    return Unsigned_integer<N>{num} / den;
}

// Modulo
template <std::size_t N>
auto operator%(std::uint64_t num, Unsigned_integer<N> const& den)
    -> Unsigned_integer<N>
{
    return Unsigned_integer<N>{num} % den;
}

template <std::size_t N>
auto operator%(std::string const& num, Unsigned_integer<N> const& den)
    -> Unsigned_integer<N>
{
    return Unsigned_integer<N>{num} % den;
}

// Multiplication
template <std::size_t N>
auto operator*(std::uint64_t lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs * lhs;
}

template <std::size_t N>
auto operator*(std::string const& lhs, Unsigned_integer<N> const& rhs)
    -> Unsigned_integer<N>
{
    return rhs * lhs;
}

// IOSTREAMS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <std::size_t N>
auto operator<<(std::ostream& os, Unsigned_integer<N> const& value)
    -> std::ostream&
{
    auto base  = 10;
    auto flags = os.flags() & std::ios::basefield;
    if (flags == std::ios::hex)
        base = 16;
    else if (flags == std::ios::oct)
        base = 8;
    os << value.to_string(base);
    return os;
}

template <std::size_t N>
auto operator>>(std::istream& is, Unsigned_integer<N>& value) -> std::istream&
{
    auto input = std::string{};
    if (is.good())
        is >> input;
    value = Unsigned_integer<N>{input};
    return is;
}

}  // namespace utility
#endif  // UTILITY_UNSIGNED_INTEGER_HPP
