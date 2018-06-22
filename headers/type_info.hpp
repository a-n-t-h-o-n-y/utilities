#ifndef UTILITY_TYPE_INFO_HPP
#define UTILITY_TYPE_INFO_HPP
#include <ostream>
#include <string>
#include <type_traits>
#include <typeindex>

#include <boost/core/demangle.hpp>

namespace utility {

/// Holds type information including cv-qualifiers and reference type.
struct Type_info {
    bool is_const;
    bool is_volatile;
    std::type_index index;
    bool is_lvalue_reference;
    bool is_rvalue_reference;

    /// Human readable representation of the type.
    operator std::string() const;
};

/// Create a Type_info object from type T.
template <typename T>
Type_info get_type_info();

/// Memberwise equality.
bool operator==(const Type_info& lhs, const Type_info& rhs);
bool operator!=(const Type_info& lhs, const Type_info& rhs);

/// Uses string conversion operator to output to stream.
std::ostream& operator<<(std::ostream& os, const Type_info& rhs);

// IMPLEMENTATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
Type_info get_type_info() {
    return Type_info{
        std::is_const<typename std::remove_reference<T>::type>::value,
        std::is_volatile<typename std::remove_reference<T>::type>::value,
        typeid(T), std::is_lvalue_reference<T>::value,
        std::is_rvalue_reference<T>::value};
}

namespace {

std::string generate_object_type_string(const Type_info& info) {
    std::string result;
    if (info.is_const) {
        result.append("const ");
    }
    if (info.is_volatile) {
        result.append("volatile ");
    }
    result.append(boost::core::demangle(info.index.name()));
    if (info.is_lvalue_reference) {
        result.append("&");
    } else if (info.is_rvalue_reference) {
        result.append("&&");
    }
    return result;
}

std::string generate_pointer_type_string(const Type_info& info) {
    std::string result{boost::core::demangle(info.index.name())};
    if (info.is_const) {
        result.append(" const");
    }
    if (info.is_volatile) {
        result.append(" volatile");
    }
    if (info.is_lvalue_reference) {
        result.append("&");
    } else if (info.is_rvalue_reference) {
        result.append("&&");
    }
    return result;
}

std::string generate_function_pointer_type_string(const Type_info& info) {
    std::string result{boost::core::demangle(info.index.name())};
    std::string qualifiers;
    if (info.is_const) {
        qualifiers.append(" const");
    }
    if (info.is_volatile) {
        qualifiers.append(" volatile");
    }
    if (info.is_lvalue_reference) {
        qualifiers.append("&");
    } else if (info.is_rvalue_reference) {
        qualifiers.append("&&");
    }
    auto pos = result.find(')');
    result.insert(pos, qualifiers);
    return result;
}

bool is_pointer_type(const std::string& name) {
    return name.back() == '*';
}

bool is_function_pointer_type(const std::string& name) {
    return name.find(')') != std::string::npos;
}

using Gen_func_t = std::string (*)(const Type_info&);
Gen_func_t find_string_generator(const Type_info& info) {
    std::string type_name{boost::core::demangle(info.index.name())};
    Gen_func_t return_func{generate_object_type_string};
    if (is_pointer_type(type_name)) {
        return_func = generate_pointer_type_string;
    } else if (is_function_pointer_type(type_name)) {
        return_func = generate_function_pointer_type_string;
    }
    return return_func;
}

}  // namespace

Type_info::operator std::string() const {
    // Generate string based on function/pointer/object type
    auto generate_string = find_string_generator(*this);
    return generate_string(*this);
}

bool operator==(const Type_info& lhs, const Type_info& rhs) {
    if (lhs.index != rhs.index) {
        return false;
    }
    return (lhs.is_const == rhs.is_const) &&
           (lhs.is_volatile == rhs.is_volatile) &&
           (lhs.is_lvalue_reference == rhs.is_lvalue_reference) &&
           (lhs.is_rvalue_reference == rhs.is_rvalue_reference);
}

bool operator!=(const Type_info& lhs, const Type_info& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Type_info& rhs) {
    os << static_cast<std::string>(rhs);
    return os;
}

}  // namespace utility

#endif  // UTILITY_TYPE_INFO_HPP
