#ifndef UTILITY_MEMORY_VIEW_HPP
#define UTILITY_MEMORY_VIEW_HPP
#include <bitset>
#include <cctype>
#include <cstddef>
#include <sstream>
#include <string>

namespace utility {
/// Used to determine output representation in a Memory_view object.
enum Representation { Binary, Decimal, Hex, Octal };

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
    void enable_seperators(bool enabled = true);

   private:
    static const std::size_t bit_n_{sizeof(T) * 8};
    bool seperators_{true};
    Representation rep_{Representation::Binary};
    std::bitset<bit_n_> bits_;

    // Initializes bitset to the raw binary representation of the value object.
    void build_bitset(const T& value);

    // Build a string from the bitset and the representation.
    std::string generate_string();

    // Inserts spaces depending on the representation and if spacing is enabled.
    void insert_seperators(std::string& rep_str);
};

// Convinience Functions - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Returns the binary representation of the given object's raw data as a
/// string. Space inserted every 4 digits(nibble) if seperators set to true.
template <typename T>
std::string as_binary(const T& value, bool seperators = true) {
    Memory_view<T> mv{value};
    mv.set_representation(Representation::Binary);
    mv.enable_seperators(seperators);
    return mv.str();
}

/// Returns the hexadecimal representation of the given object's raw data as a
/// string. Space inserted every 2 digits(byte) if seperators set to true.
template <typename T>
std::string as_hex(const T& value, bool seperators = true) {
    Memory_view<T> mv{value};
    mv.set_representation(Representation::Hex);
    mv.enable_seperators(seperators);
    return mv.str();
}

/// Returns the decimal representation of the given object's raw data as a
/// string. Comma inserted every 3 digits if seperators set to true.
template <typename T>
std::string as_decimal(const T& value, bool seperators = true) {
    Memory_view<T> mv{value};
    mv.set_representation(Representation::Decimal);
    mv.enable_seperators(seperators);
    return mv.str();
}

/// Returns the Octal representation of the given object's raw data as a
/// string. No seperators availiable.
template <typename T>
std::string as_octal(const T& value) {
    Memory_view<T> mv{value};
    mv.set_representation(Representation::Octal);
    mv.enable_seperators(false);
    return mv.str();
}

// Implementations - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename T>
Memory_view<T>::Memory_view(const T& value) {
    this->build_bitset(value);
}

template <typename T>
void Memory_view<T>::build_bitset(const T& value) {
    const unsigned char* address_ =
        reinterpret_cast<const unsigned char*>(&value);
    int position{0};
    for (std::size_t i{0}; i < bit_n_; ++i) {
        bits_[i] = address_[i / 8] >> position & 0x01 ? true : false;
        ++position;
        position %= 8;
    }
}

template <typename T>
std::string Memory_view<T>::str() {
    std::string string_representation{this->generate_string()};
    this->insert_seperators(string_representation);
    return string_representation;
}

template <typename T>
void Memory_view<T>::set_representation(Representation rep) {
    rep_ = rep;
}

template <typename T>
void Memory_view<T>::enable_seperators(bool enabled) {
    seperators_ = enabled;
}

template <typename T>
std::string Memory_view<T>::generate_string() {
    std::size_t ull_bit_n{sizeof(unsigned long long) * 8};
    if (rep_ == Representation::Binary) {
        return bits_.to_string();
    } else if (rep_ == Representation::Decimal) {
        if (ull_bit_n < bits_.size()) {
            return "";
        }
        unsigned long long val{bits_.to_ullong()};
        std::stringstream ss;
        ss << std::dec << val;
        return ss.str();
    } else if (rep_ == Representation::Hex) {
        if (ull_bit_n < bits_.size()) {
            return "";
        }
        unsigned long long val{bits_.to_ullong()};
        std::stringstream ss;
        ss << std::hex << val;
        auto hex_str = ss.str();
        for (char& c : hex_str) {
            c = std::toupper(c);
        }
        return hex_str;
    } else if (rep_ == Representation::Octal) {
        if (ull_bit_n < bits_.size()) {
            return "";
        }
        unsigned long long val{bits_.to_ullong()};
        std::stringstream ss;
        ss << std::oct << val;
        return ss.str();
    }
    return "";
}

template <typename T>
void Memory_view<T>::insert_seperators(std::string& rep_str) {
    if (seperators_ == false) {
        return;
    }

    // Insert seperator c, every n digits, right to left.
    auto insert_seps = [](std::string& str, char c, std::size_t n) {
        int count{0};
        for (std::size_t i{str.size() - 1}; i < str.size(); --i) {
            if ((count + 1) % n == 0 && i != 0) {
                str.insert(i, 1, c);
            }
            ++count;
        }
    };

    if (rep_ == Representation::Binary) {
        insert_seps(rep_str, ' ', 4);
    } else if (rep_ == Representation::Hex) {
        insert_seps(rep_str, ' ', 2);
    } else if (rep_ == Representation::Decimal) {
        insert_seps(rep_str, ',', 3);
    }
}

}  // namespace utility
#endif  // UTILITY_MEMORY_VIEW_HPP
