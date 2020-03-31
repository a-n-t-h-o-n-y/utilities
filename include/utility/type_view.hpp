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
void primary_categories(std::ostream& os = std::cout)
{
    using namespace std;
    os << "-- Primary Categories --\n";
    os << boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_void: " << is_void_v<T> << "\nis_null_pointer: "
       << is_null_pointer_v<T> << "\nis_integral: "
       << is_integral_v<T> << "\nis_floating_point: "
       << is_floating_point_v<T> << "\nis_array: "
       << is_array_v<T> << "\nis_enum: " << is_enum_v<T> << "\nis_union: "
       << is_union_v<T> << "\nis_class: " << is_class_v<T> << "\nis_function: "
       << is_function_v<T> << "\nis_pointer: "
       << is_pointer_v<T> << "\nis_lvalue_reference: "
       << is_lvalue_reference_v<T> << "\nis_rvalue_reference: "
       << is_rvalue_reference_v<T> << "\nis_member_object_pointer: "
       << is_member_object_pointer_v<T> << "\nis_member_function_pointer: "
       << is_member_function_pointer_v<T> << '\n';
}

/// Output all type_trait values from 'Composite Type Categories' subgroup.
template <typename T>
void composite_categories(std::ostream& os = std::cout)
{
    using namespace std;
    os << "-- Composite Categories --\n";
    os << boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_fundamental: " << is_fundamental_v<T> << "\nis_arithmetic: "
       << is_arithmetic_v<T> << "\nis_scalar: "
       << is_scalar_v<T> << "\nis_object: "
       << is_object_v<T> << "\nis_compound: "
       << is_compound_v<T> << "\nis_reference: "
       << is_reference_v<T> << "\nis_member_pointer: "
       << is_member_pointer_v<T> << '\n';
}

/// Output all type_trait values from 'Type Properties' subgroup.
template <typename T>
void type_properties(std::ostream& os = std::cout)
{
    using namespace std;
    os << "-- Type Properties --\n";
    os << boolalpha << "Type name: " << typeid(T).name();
    os << "\nis_const: " << is_const_v<T> << "\nis_volatile: "
       << is_volatile_v<T> << "\nis_trivial: "
       << is_trivial_v<T> << "\nis_trivially_copyable: "
       << is_trivially_copyable_v<T> << "\nis_standard_layout: "
       << is_standard_layout_v<T> << "\nis_pod: "
       << is_pod_v<T> << "\nis_literal_type: "
       << is_literal_type_v<T> << "\nis_empty: "
       << is_empty_v<T> << "\nis_polymorphic: "
       << is_polymorphic_v<T> << "\nis_abstract: "
       << is_abstract_v<T> << "\nis_final: " << is_final_v<T> << "\nis_signed: "
       << is_signed_v<T> << "\nis_unsigned: " << is_unsigned_v<T> << '\n';
}

/// Output all type_trait values from 'Supported Operations' subgroup.
/// Type U used for is_assignable variants as the type assigned to type T.
template <typename T, typename U = T>
void operations(std::ostream& os = std::cout)
{
    using namespace std;
    os << "-- Operations --\n";
    os << boolalpha << "Type name(T): " << typeid(T).name();
    os << "\nType name(U): " << typeid(U).name();
    os << "\nis_constructible: "
       << is_constructible_v<T> << "\nis_trivially_constructible: "
       << is_trivially_constructible_v<T> << "\nis_nothrow_constructible: "
       << is_nothrow_constructible_v<T> << "\nis_default_constructible: "
       << is_default_constructible_v<
              T> << "\nis_trivially_default_constructible: "
       << is_trivially_default_constructible_v<
              T> << "\nis_nothrow_default_constructible: "
       << is_nothrow_default_constructible_v<T> << "\nis_copy_constructible: "
       << is_copy_constructible_v<T> << "\nis_trivially_copy_constructible: "
       << is_trivially_copy_constructible_v<
              T> << "\nis_nothrow_copy_constructible: "
       << is_nothrow_copy_constructible_v<T> << "\nis_move_constructible: "
       << is_move_constructible_v<T> << "\nis_trivially_move_constructible: "
       << is_trivially_move_constructible_v<
              T> << "\nis_nothrow_move_constructible: "
       << is_nothrow_move_constructible_v<T> << "\nis_assignable(T->U): "
       << is_assignable_v<T, U> << "\nis_trivially_assignable(T->U): "
       << is_trivially_assignable_v<T, U> << "\nis_nothrow_assignable(T->U): "
       << is_nothrow_assignable_v<T, U> << "\nis_copy_assignable: "
       << is_copy_assignable_v<T> << "\nis_trivially_copy_assignable: "
       << is_trivially_copy_assignable_v<T> << "\nis_nothrow_copy_assignable: "
       << is_nothrow_copy_assignable_v<T> << "\nis_move_assignable: "
       << is_move_assignable_v<T> << "\nis_trivially_move_assignable: "
       << is_trivially_move_assignable_v<T> << "\nis_nothrow_move_assignable: "
       << is_nothrow_move_assignable_v<T> << "\nis_destructible: "
       << is_destructible_v<T> << "\nis_trivially_destructible: "
       << is_trivially_destructible_v<T> << "\nis_nothrow_destructible: "
       << is_nothrow_destructible_v<T> << "\nhas_virtual_destructor: "
       << has_virtual_destructor_v<T> << '\n';
}

/// Output all type_trait values from 'Property Queries' subgroup.
template <typename T, unsigned N = 0>
void property_queries(std::ostream& os = std::cout)
{
    os << "-- Property Queries --\n";
    os << "Type name: " << typeid(T).name();
    os << "\nalignment_of: " << std::alignment_of_v<T> << "\nrank: "
       << std::rank_v<T> << "\nextent: " << std::extent_v<T, N> << '\n';
}

/// Output all type_trait values from 'Type Relationships' subgroup.
template <typename T, typename U = T>
void type_relationships(std::ostream& os = std::cout)
{
    os << "-- Type Relationships --\n";
    os << std::boolalpha << "Type name(T): " << typeid(T).name();
    os << "\nType name(U): " << typeid(U).name();
    os << "\nis_same: " << std::is_same_v<T, U> << "\nis_base_of: "
       << std::is_base_of_v<T, U> << "\nis_convertible: "
       << std::is_convertible_v<T, U> << '\n';
}

/// Output all values from std::numeric_limits.
template <typename T>
void limits(std::ostream& os = std::cout)
{
    using lims = std::numeric_limits<T>;
    os << "-- Numeric Limits --\n";
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
       << "\ndenorm_min: " << lims::denorm_min() << '\n';
}

}  // namespace type_view

template <typename T, typename U = T>
void type_view_all(std::ostream& os = std::cout)
{
    using namespace type_view;
    primary_categories<T>(os);
    os << '\n';
    composite_categories<T>(os);
    os << '\n';
    type_properties<T>(os);
    os << '\n';
    operations<T, U>(os);
    os << '\n';
    property_queries<T>(os);
    os << '\n';
    type_relationships<T, U>(os);
    os << '\n';
    limits<T>(os);
}

}  // namespace utility
#endif  // UTILITY_TYPE_VIEW_HPP
