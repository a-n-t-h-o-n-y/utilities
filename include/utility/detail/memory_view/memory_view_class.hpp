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

namespace utility::detail::memory_view {

/// Provides functions to output raw data representation of an object of type T.
/// Data Types larger than size_of(unsigned long long), typically 8 bytes, can
/// only be displayed as binary.
template <typename T>
class Memory_view {
   public:
    /// Initialize with any value.
    Memory_view(T const& value) { this->build_bitset(value); }

    /// Return string representation of value. Uses the currently set
    /// representation and spacing.
    auto str() -> std::string
    {
        auto string_rep = this->generate_string();
        this->insert_separators(string_rep);
        return string_rep;
    }

    /// Set the string output representation of the value.
    void set_representation(Representation rep) { rep_ = rep; }

    /// Enable/Disable spaces/commas in output representation for readability.
    void enable_separators(bool enabled = true) { separators_ = enabled; }

   private:
    std::bitset<sizeof(T) * 8> bits_;
    bool separators_    = true;
    Representation rep_ = Representation::Binary;

   private:
    // Initializes bitset to the raw binary representation of the value object.
    void build_bitset(T const& value)
    {
        auto const address = reinterpret_cast<unsigned char const*>(&value);
        for (auto i = 0uL; i < bits_.size(); ++i)
            bits_[i] = bit_at(address, i);
    }

    // Build a string from the bitset and the representation.
    auto generate_string() -> std::string
    {
        if (rep_ == Representation::Binary)
            return bits_.to_string();
        return format_to_string(bits_, get_base_flag(rep_));
    }

    // Inserts spaces depending on the representation and if spacing is enabled.
    void insert_separators(std::string& rep_str)
    {
        if (!separators_)
            return;
        auto insert_every = [&rep_str](char c, std::size_t n) {
            for (std::int64_t i = rep_str.size() - n; i > 0; i -= n)
                rep_str.insert(i, 1, c);
        };
        switch (rep_) {
            case Representation::Binary: insert_every(' ', 4); break;
            case Representation::Hex: insert_every(' ', 2); break;
            case Representation::Decimal: insert_every(',', 3); break;
            default: break;
        }
    }
};

}  // namespace utility::detail::memory_view
#endif  // UTILITY_DETAIL_MEMORY_VIEW_MEMORY_VIEW_CLASS_HPP
