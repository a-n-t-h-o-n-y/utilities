#ifndef UTILITY_TYPE_INFO_HPP
#define UTILITY_TYPE_INFO_HPP
#include <ostream>
#include <string>
#include <type_traits>
#include <typeindex>

#include <boost/core/demangle.hpp>

namespace utility {

/// Holds type information including cv-qualifiers and reference type.
class Type_info {
   public:
    bool is_const;
    bool is_volatile;
    std::type_index index;
    bool is_lvalue_reference;
    bool is_rvalue_reference;

   public:
    /// cv-qualified, unmangled type name with reference.
    auto full_type_name() const -> std::string
    {
        // Generate string based on function/pointer/object type.
        auto generate_string_fn = Type_info::find_string_generator(*this);
        return generate_string_fn(*this);
    }

    /// Core type name, unqualified with reference removed.
    auto type_name() const -> std::string { return demangle(*this); }

    /// Converts to full_type_name()
    operator std::string() const { return this->full_type_name(); }

   private:
    static auto demangle(Type_info const& info) -> std::string
    {
        return boost::core::demangle(info.index.name());
    }

    static auto generate_object_type_string(Type_info const& info)
        -> std::string
    {
        auto result = std::string{};
        if (info.is_const)
            result.append("const ");
        if (info.is_volatile)
            result.append("volatile ");
        result.append(demangle(info));
        if (info.is_lvalue_reference)
            result.append("&");
        else if (info.is_rvalue_reference)
            result.append("&&");
        return result;
    }

    static auto generate_pointer_type_string(Type_info const& info)
        -> std::string
    {
        auto result = demangle(info);
        if (info.is_const)
            result.append(" const");
        if (info.is_volatile)
            result.append(" volatile");
        if (info.is_lvalue_reference)
            result.append("&");
        else if (info.is_rvalue_reference)
            result.append("&&");
        return result;
    }

    static auto generate_function_pointer_type_string(Type_info const& info)
        -> std::string
    {
        auto qualifiers = std::string{""};
        if (info.is_const)
            qualifiers.append(" const");
        if (info.is_volatile)
            qualifiers.append(" volatile");
        if (info.is_lvalue_reference)
            qualifiers.append("&");
        else if (info.is_rvalue_reference)
            qualifiers.append("&&");
        auto result = demangle(info);
        result.insert(result.find(')'), qualifiers);
        return result;
    }

    static auto is_pointer_type(std::string const& name) -> bool
    {
        return name.back() == '*';
    }

    static auto is_function_pointer_type(std::string const& name) -> bool
    {
        return name.find(')') != std::string::npos;
    }

    using Generator_fn_t = std::string (*)(Type_info const&);

    static auto find_string_generator(Type_info const& info) -> Generator_fn_t
    {
        auto const type_name = demangle(info);
        if (is_pointer_type(type_name))
            return generate_pointer_type_string;
        else if (is_function_pointer_type(type_name))
            return generate_function_pointer_type_string;
        else
            return generate_object_type_string;
    }
};

/// Create a Type_info object from type T.
template <typename T>
auto get_type_info() -> Type_info
{
    return {std::is_const_v<typename std::remove_reference<T>::type>,
            std::is_volatile_v<typename std::remove_reference<T>::type>,
            typeid(T), std::is_lvalue_reference_v<T>,
            std::is_rvalue_reference_v<T>};
}

/// Memberwise equality.
inline auto operator==(Type_info const& lhs, Type_info const& rhs) -> bool
{
    if (lhs.index != rhs.index)
        return false;
    return (lhs.is_const == rhs.is_const) &&
           (lhs.is_volatile == rhs.is_volatile) &&
           (lhs.is_lvalue_reference == rhs.is_lvalue_reference) &&
           (lhs.is_rvalue_reference == rhs.is_rvalue_reference);
}

inline auto operator!=(Type_info const& lhs, Type_info const& rhs) -> bool
{
    return !(lhs == rhs);
}

/// Provides unique ordering.
inline auto operator<(Type_info const& lhs, Type_info const& rhs) -> bool
{
    if (lhs.index != rhs.index)
        return lhs.index < rhs.index;

    if (!lhs.is_const && rhs.is_const)
        return true;
    else if (lhs.is_const && !rhs.is_const)
        return false;

    if (!lhs.is_volatile && rhs.is_volatile)
        return true;
    else if (lhs.is_volatile && !rhs.is_volatile)
        return false;

    if (!lhs.is_lvalue_reference && rhs.is_lvalue_reference)
        return true;
    else if (lhs.is_lvalue_reference && !rhs.is_lvalue_reference)
        return false;

    if (!lhs.is_rvalue_reference && rhs.is_rvalue_reference)
        return true;
    else if (lhs.is_rvalue_reference && !rhs.is_rvalue_reference)
        return false;

    return false;
}

/// Uses string conversion operator to output to stream.
inline auto operator<<(std::ostream& os, Type_info const& rhs) -> std::ostream&
{
    os << static_cast<std::string>(rhs);
    return os;
}

}  // namespace utility
#endif  // UTILITY_TYPE_INFO_HPP
