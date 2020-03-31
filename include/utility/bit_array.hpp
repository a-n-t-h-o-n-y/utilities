#ifndef UTILITY_BIT_ARRAY_HPP
#define UTILITY_BIT_ARRAY_HPP
#include <climits>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>

namespace utility {

/// Holds an array of bools with a built in data type.
/** Size is equal to the number of bits in the data type. Array types work,
 *  bools and floats do not.*/
template <typename Storage_t>
class Bit_array {
   public:
    /// Default construct with all values false.
    constexpr Bit_array() = default;

    /// Construct with initializer list.
    /** Allows for partial constructions with remaining values set to false. */
    constexpr Bit_array(std::initializer_list<bool> const& init)
    {
        auto i = std::size_t{0};
        for (bool b : init)
            this->set(i++, b);
    }

    // Const Forward Iterator
    class Const_iterator {
       public:
        constexpr auto operator++() -> Const_iterator&
        {
            ++index_;
            return *this;
        }

        constexpr auto operator++(int) -> Const_iterator
        {
            auto temp = Const_iterator{*this};
            this->operator++();
            return temp;
        }

        constexpr auto operator*() const -> bool { return array_[index_]; }

        constexpr auto operator==(Const_iterator const& iter) -> bool
        {
            return (&array_ == &iter.array_) && (index_ == iter.index_);
        }

        constexpr auto operator!=(Const_iterator const& iter) -> bool
        {
            return !(*this == iter);
        }

       private:
        Bit_array const& array_;
        std::size_t index_;

       private:
        friend Bit_array;
        constexpr Const_iterator(Bit_array const& array, std::size_t index_init)
            : array_{array}, index_{index_init}
        {}
    };

    /// Return a const forward iterator to the first element.
    constexpr auto begin() const -> Const_iterator { return {*this, 0}; }

    /// Return a const forward iterator to the one past the end element.
    constexpr auto end() const -> Const_iterator
    {
        return {*this, this->size()};
    }

    /// Return the value at index \p position.
    /** No bounds checking. */
    constexpr auto operator[](std::size_t position) const -> bool
    {
        if constexpr (std::is_array_v<Storage_t>) {
            auto const bit_count = unit_bit_count();
            return data_[position / bit_count] &
                   (unit() << (position % bit_count));
        }
        else
            return data_ & (unit() << position);
    }

    /// Return the value at index \p position.
    /** Throws std::out_of_range if \p position is >= size(). */
    constexpr auto at(std::size_t position) const -> bool
    {
        if (position >= this->size())
            throw std::out_of_range{"Out of bounds access"};
        return (*this)[position];
    }

    /// Set the value at index \p position.
    /** No bounds checking. */
    constexpr void set(std::size_t position, bool value)
    {
        if constexpr (std::is_array_v<Storage_t>) {
            auto const bit_count = unit_bit_count();
            value ? data_[position / bit_count] |= unit()
                                                   << (position % bit_count)
                  : data_[position / bit_count] &=
                    ~(unit() << (position % bit_count));
        }
        else {
            value ? data_ |= unit() << position
                  : data_ &= ~(unit() << position);
        }
    }

    /// Return the number of elements in the container.
    constexpr static auto size() -> std::size_t
    {
        return sizeof(Storage_t) * CHAR_BIT;
    }

   private:
    Storage_t data_ = {0};

   private:
    /// Return number of bits in a single object of the type held by Storage_t.
    /** Only for array types. */
    constexpr auto unit_bit_count() const -> std::size_t
    {
        return sizeof(data_[0]) * CHAR_BIT;
    }

    /// Return the value 1.
    /** The type returned is Storage_t if it is not an array, and the type held
     *  by an array Storage_t if it is. Used for safe bit shifting. */
    static constexpr auto unit()
    {
        if constexpr (std::is_array_v<Storage_t>)
            return std::remove_reference_t<decltype(data_[0])>(1);
        else
            return Storage_t(1);
    }
};

}  // namespace utility
#endif  // UTILITY_BIT_ARRAY_HPP
