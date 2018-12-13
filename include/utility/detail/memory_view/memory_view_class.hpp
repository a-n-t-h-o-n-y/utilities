#ifndef UTILITY_DETAIL_MEMORY_VIEW_MEMORY_VIEW_CLASS_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_MEMORY_VIEW_CLASS_HPP
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <string>

#include "bit_at.hpp"
#include "format_to_string.hpp"
#include "get_base_flag.hpp"
#include "representation.hpp"

namespace utility {
namespace detail {
namespace memory_view {

/// Provides functions to output raw data representation of an object of type T.
/// Data Types larger than size_of(unsigned long long), typically 8 bytes, can
/// only be displayed as binary.
template <typename T>
class Memory_view {
   public:
    /// Initialize with any value.
    Memory_view(const T& value);

    /// Return string representation of value. Uses the currently set
    /// representation and spacing.
    std::string str();

    /// Set the string output representation of the value.
    void set_representation(Representation rep);

    /// Enable/Disable spaces/commas in output representation for readability.
    void enable_separators(bool enabled = true);

   private:
    std::bitset<sizeof(T) * 8> bits_;
    bool separators_{true};
    Representation rep_{Representation::Binary};

    // Initializes bitset to the raw binary representation of the value object.
    void build_bitset(const T& value);

    // Build a string from the bitset and the representation.
    std::string generate_string();

    // Inserts spaces depending on the representation and if spacing is enabled.
    void insert_separators(std::string& rep_str);
};

// Implementations - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename T>
Memory_view<T>::Memory_view(const T& value) {
    this->build_bitset(value);
}

template <typename T>
void Memory_view<T>::build_bitset(const T& value) {
    const auto* address = reinterpret_cast<const unsigned char*>(&value);
    for (auto i = 0uL; i < bits_.size(); ++i) {
        bits_[i] = bit_at(address, i);
    }
}

template <typename T>
std::string Memory_view<T>::str() {
    auto string_rep = this->generate_string();
    this->insert_separators(string_rep);
    return string_rep;
}

template <typename T>
void Memory_view<T>::set_representation(Representation rep) {
    rep_ = rep;
}

template <typename T>
void Memory_view<T>::enable_separators(bool enabled) {
    separators_ = enabled;
}

template <typename T>
std::string Memory_view<T>::generate_string() {
    if (rep_ == Representation::Binary) {
        return bits_.to_string();
    }
    return format_to_string(bits_, get_base_flag(rep_));
}

template <typename T>
void Memory_view<T>::insert_separators(std::string& string_rep) {
    if (!separators_) {
        return;
    }
    auto insert_every = [&string_rep](char c, std::size_t n) {
        for (std::int64_t i = string_rep.size() - n; i > 0; i -= n) {
            string_rep.insert(i, 1, c);
        }
    };
    switch (rep_) {
        case Representation::Binary:
            insert_every(' ', 4);
            break;
        case Representation::Hex:
            insert_every(' ', 2);
            break;
        case Representation::Decimal:
            insert_every(',', 3);
            break;
        default:
            break;
    }
}

}  // namespace memory_view
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_MEMORY_VIEW_MEMORY_VIEW_CLASS_HPP
