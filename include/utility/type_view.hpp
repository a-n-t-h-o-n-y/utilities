#ifndef UTILITY_TYPE_VIEW_HPP
#define UTILITY_TYPE_VIEW_HPP
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>

namespace utility {
namespace type_view {

/// Output all type_trait values from 'Primary Type Categories' subgroup.
template <typename T>
void primary_categories(std::ostream& os = std::cout) {
    os << "-- Primary Categories --\n";
    os << std::boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_void: " << std::is_void<T>::value

       << "\nis_null_pointer: " << std::is_null_pointer<T>::value

       << "\nis_integral: " << std::is_integral<T>::value

       << "\nis_floating_point: " << std::is_floating_point<T>::value

       << "\nis_array: " << std::is_array<T>::value

       << "\nis_enum: " << std::is_enum<T>::value

       << "\nis_union: " << std::is_union<T>::value

       << "\nis_class: " << std::is_class<T>::value

       << "\nis_function: " << std::is_function<T>::value

       << "\nis_pointer: " << std::is_pointer<T>::value

       << "\nis_lvalue_reference: " << std::is_lvalue_reference<T>::value

       << "\nis_rvalue_reference: " << std::is_rvalue_reference<T>::value

       << "\nis_member_object_pointer: "
       << std::is_member_object_pointer<T>::value

       << "\nis_member_function_pointer: "
       << std::is_member_function_pointer<T>::value

       << std::endl;
}

/// Output all type_trait values from 'Composite Type Categories' subgroup.
template <typename T>
void composite_categories(std::ostream& os = std::cout) {
    os << "-- Composite Categories --\n";
    os << std::boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_fundamental: " << std::is_fundamental<T>::value
       << "\nis_arithmetic: " << std::is_arithmetic<T>::value
       << "\nis_scalar: " << std::is_scalar<T>::value
       << "\nis_object: " << std::is_object<T>::value
       << "\nis_compound: " << std::is_compound<T>::value
       << "\nis_reference: " << std::is_reference<T>::value
       << "\nis_member_pointer: " << std::is_member_pointer<T>::value
       << std::endl;
}

/// Output all type_trait values from 'Type Properties' subgroup.
template <typename T>
void type_properties(std::ostream& os = std::cout) {
    os << "-- Type Properties --\n";
    os << std::boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_const: " << std::is_const<T>::value
       << "\nis_volatile: " << std::is_volatile<T>::value
       << "\nis_trivial: " << std::is_trivial<T>::value
       << "\nis_trivially_copyable: " << std::is_trivially_copyable<T>::value
       << "\nis_standard_layout: " << std::is_standard_layout<T>::value
       << "\nis_pod: " << std::is_pod<T>::value
       << "\nis_literal_type: " << std::is_literal_type<T>::value
       << "\nis_empty: " << std::is_empty<T>::value
       << "\nis_polymorphic: " << std::is_polymorphic<T>::value
       << "\nis_abstract: " << std::is_abstract<T>::value
       << "\nis_final: " << std::is_final<T>::value
       << "\nis_signed: " << std::is_signed<T>::value
       << "\nis_unsigned: " << std::is_unsigned<T>::value << std::endl;
}

/// Output all type_trait values from 'Supported Operations' subgroup.
/// Type U used for is_assignable variants as the type assigned to type T.
template <typename T, typename U = T>
void operations(std::ostream& os = std::cout) {
    os << "-- Operations --\n";
    os << std::boolalpha << "Type name(T): " << typeid(T).name();
    os << "\nType name(U): " << typeid(U).name();
    os << "\nis_constructible: " << std::is_constructible<T>::value

       << "\nis_trivially_constructible: "
       << std::is_trivially_constructible<T>::value

       << "\nis_nothrow_constructible: "
       << std::is_nothrow_constructible<T>::value

       << "\nis_default_constructible: "
       << std::is_default_constructible<T>::value

       << "\nis_trivially_default_constructible: "
       << std::is_trivially_default_constructible<T>::value

       << "\nis_nothrow_default_constructible: "
       << std::is_nothrow_default_constructible<T>::value

       << "\nis_copy_constructible: " << std::is_copy_constructible<T>::value

       << "\nis_trivially_copy_constructible: "
       << std::is_trivially_copy_constructible<T>::value

       << "\nis_nothrow_copy_constructible: "
       << std::is_nothrow_copy_constructible<T>::value

       << "\nis_move_constructible: " << std::is_move_constructible<T>::value

       << "\nis_trivially_move_constructible: "
       << std::is_trivially_move_constructible<T>::value

       << "\nis_nothrow_move_constructible: "
       << std::is_nothrow_move_constructible<T>::value

       << "\nis_assignable(T->U): " << std::is_assignable<T, U>::value

       << "\nis_trivially_assignable(T->U): "
       << std::is_trivially_assignable<T, U>::value

       << "\nis_nothrow_assignable(T->U): "
       << std::is_nothrow_assignable<T, U>::value

       << "\nis_copy_assignable: " << std::is_copy_assignable<T>::value

       << "\nis_trivially_copy_assignable: "
       << std::is_trivially_copy_assignable<T>::value

       << "\nis_nothrow_copy_assignable: "
       << std::is_nothrow_copy_assignable<T>::value

       << "\nis_move_assignable: " << std::is_move_assignable<T>::value

       << "\nis_trivially_move_assignable: "
       << std::is_trivially_move_assignable<T>::value

       << "\nis_nothrow_move_assignable: "
       << std::is_nothrow_move_assignable<T>::value

       << "\nis_destructible: " << std::is_destructible<T>::value

       << "\nis_trivially_destructible: "
       << std::is_trivially_destructible<T>::value

       << "\nis_nothrow_destructible: "
       << std::is_nothrow_destructible<T>::value

       << "\nhas_virtual_destructor: " << std::has_virtual_destructor<T>::value

       << std::endl;
}

/// Output all type_trait values from 'Property Queries' subgroup.
template <typename T, unsigned N = 0>
void property_queries(std::ostream& os = std::cout) {
    os << "-- Property Queries --\n";
    os << "Type name: " << typeid(T).name();
    os << "\nalignment_of: " << std::alignment_of<T>::value
       << "\nrank: " << std::rank<T>::value
       << "\nextent: " << std::extent<T, N>::value << std::endl;
}

/// Output all type_trait values from 'Type Relationships' subgroup.
template <typename T, typename U = T>
void type_relationships(std::ostream& os = std::cout) {
    os << "-- Type Relationships --\n";
    os << std::boolalpha << "Type name(T): " << typeid(T).name();
    os << "\nType name(U): " << typeid(U).name();
    os << "\nis_same: " << std::is_same<T, U>::value
       << "\nis_base_of: " << std::is_base_of<T, U>::value
       << "\nis_convertible: " << std::is_convertible<T, U>::value << std::endl;
}

/// Output all values from std::numeric_limits.
template <typename T>
void limits(std::ostream& os = std::cout) {
    os << "-- Numeric Limits --\n";
    using lims = std::numeric_limits<T>;
    os << std::boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_specialized: " << lims::is_specialized
       << "\nis_signed: " << lims::is_signed
       << "\nis_integer: " << lims::is_integer
       << "\nis_exact: " << lims::is_exact
       << "\nhas_infinity: " << lims::has_infinity
       << "\nhas_quiet_NaN: " << lims::has_quiet_NaN
       << "\nhas_signaling_NaN: " << lims::has_signaling_NaN
       << "\nhas_denorm: " << lims::has_denorm
       << "\nhas_denorm_loss: " << lims::has_denorm_loss
       << "\nround_style: " << lims::round_style
       << "\nis_iec559: " << lims::is_iec559
       << "\nis_bounded: " << lims::is_bounded
       << "\nis_modulo: " << lims::is_modulo << "\ndigits: " << lims::digits
       << "\ndigits10: " << lims::digits10
       << "\nmax_digits10: " << lims::max_digits10 << "\nradix: " << lims::radix
       << "\nmin_exponent: " << lims::min_exponent
       << "\nmin_exponent10: " << lims::min_exponent10
       << "\nmax_exponent: " << lims::max_exponent
       << "\nmax_exponent10: " << lims::max_exponent10
       << "\ntraps: " << lims::traps
       << "\ntinyness_before: " << lims::tinyness_before
       << "\nmin: " << lims::min() << "\nlowest: " << lims::lowest()
       << "\nmax: " << lims::max() << "\nepsilon: " << lims::epsilon()
       << "\nround_error: " << lims::round_error()
       << "\ninfinity: " << lims::infinity()
       << "\nquiet_NaN: " << lims::quiet_NaN()
       << "\nsignaling_NaN: " << lims::signaling_NaN()
       << "\ndenorm_min: " << lims::denorm_min() << std::endl;
}

}  // namespace type_view

template <typename T, typename U = T>
void type_view_all(std::ostream& os = std::cout) {
    type_view::primary_categories<T>(os);
    os << '\n';
    type_view::composite_categories<T>(os);
    os << '\n';
    type_view::type_properties<T>(os);
    os << '\n';
    type_view::operations<T, U>(os);
    os << '\n';
    type_view::property_queries<T>(os);
    os << '\n';
    type_view::type_relationships<T, U>(os);
    os << '\n';
    type_view::limits<T>(os);
}

}  // namespace utility
#endif  // UTILITY_TYPE_VIEW_HPP
