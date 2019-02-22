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
    Storage_t data_ = {0};

    /// Return number of bits in a single object of the type held by Storage_t.
    /** Only for array types. */
    constexpr std::size_t unit_bit_count() const {
        return sizeof(data_[0]) * CHAR_BIT;
    }

    /// Return the value 1.
    /** The type returned is Storage_t if it is not an array, and the type held
     *  by an array Storage_t if it is. Used for safe bit shifting. */
    static constexpr auto unit() {
        if constexpr (std::is_array_v<Storage_t>) {
            return std::remove_reference_t<decltype(data_[0])>(1);
        } else {
            return Storage_t(1);
        }
    }

   public:
    using Size_t = std::size_t;

    /// Default construct with all values false.
    constexpr Bit_array() = default;

    /// Construct with initializer list.
    /** Allows for partial constructions with remaining values set to false. */
    constexpr Bit_array(const std::initializer_list<bool>& init) {
        Size_t i{0};
        for (bool b : init) {
            this->set(i++, b);
        }
    }

    // Const Forward Iterator
    class Const_iterator {
        const Bit_array& array_;
        Size_t index_;

        constexpr Const_iterator(const Bit_array& array, Size_t index_init = 0)
            : array_{array}, index_{index_init} {}

       public:
        friend Bit_array;

        constexpr Const_iterator& operator++() {
            ++index_;
            return *this;
        }

        constexpr Const_iterator operator++(int) {
            auto temp = Const_iterator{*this};
            this->operator++();
            return temp;
        }

        constexpr bool operator*() const { return array_[index_]; }

        constexpr bool operator==(const Const_iterator& iter) {
            return (&array_ == &iter.array_) && (index_ == iter.index_);
        }
        constexpr bool operator!=(const Const_iterator& iter) {
            return !(*this == iter);
        }
    };

    /// Return a const forward iterator to the first element.
    constexpr Const_iterator begin() const { return {*this, 0}; }

    /// Return a const forward iterator to the one past the end element.
    constexpr Const_iterator end() const { return {*this, this->size()}; }

    /// Return the value at index \p position.
    /** No bounds checking. */
    constexpr bool operator[](Size_t position) const {
        if constexpr (std::is_array_v<Storage_t>) {
            const auto bit_count = unit_bit_count();
            return data_[position / bit_count] &
                   (unit() << (position % bit_count));
        } else {
            return data_ & (unit() << position);
        }
    }

    /// Return the value at index \p position.
    /** Throws std::out_of_range if \p position is >= size(). */
    constexpr bool at(Size_t position) const {
        if (position >= this->size()) {
            throw std::out_of_range{"Out of bounds access."};
        }
        return (*this)[position];
    }

    /// Set the value at index \p position.
    /** No bounds checking. */
    constexpr void set(Size_t position, bool value) {
        if constexpr (std::is_array_v<Storage_t>) {
            const auto bit_count = unit_bit_count();
            value ? data_[position / bit_count] |= unit()
                                                   << (position % bit_count)
                  : data_[position / bit_count] &=
                    ~(unit() << (position % bit_count));
        } else {
            value ? data_ |= unit() << position
                  : data_ &= ~(unit() << position);
        }
    }

    /// Return the number of elements in the container.
    constexpr static Size_t size() { return sizeof(Storage_t) * CHAR_BIT; }
};

}  // namespace utility
#endif  // UTILITY_BIT_ARRAY_HPP
