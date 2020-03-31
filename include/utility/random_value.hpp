#ifndef UTILITIES_RANDOM_VALUE_HPP
#define UTILITIES_RANDOM_VALUE_HPP
#include <cstddef>
#include <iterator>
#include <type_traits>

#include "detail/is_std_array.hpp"
#include "detail/random_value/gen_value.hpp"

using namespace utility::detail::random_value;

namespace utility {

/// Generate a single integral type value.
/** Bounds are inclusive. */
template <typename Int_t,
          typename std::enable_if_t<std::is_integral_v<Int_t>, int> = 0>
auto random_value(Int_t lower_bound, Int_t upper_bound) -> Int_t
{
    return gen_int_type(lower_bound, upper_bound);
}

/// Generate a single random floating point type value.
/** Bounds are inclusive. */
template <typename Float_t,
          typename std::enable_if_t<std::is_floating_point_v<Float_t>, int> = 0>
auto random_value(Float_t lower_bound, Float_t upper_bound) -> Float_t
{
    return gen_float_type(static_cast<Float_t>(lower_bound),
                          static_cast<Float_t>(upper_bound));
}

/// Generate a single random value - non-integral and non-floating point types.
/** Type must have a conversion from Int_t. Bounds are inclusive.*/
template <typename Value_t,
          typename Int_t,
          typename std::enable_if_t<not std::is_integral_v<Value_t> &&
                                        not std::is_floating_point_v<Value_t>,
                                    int> = 0>
auto random_value(Int_t lower_bound, Int_t upper_bound) -> Value_t
{
    return static_cast<Value_t>(gen_int_type(lower_bound, upper_bound));
}

/// Generate a container of random values.
/** Container_t != array; value_type == integral type.
 * Bounds are inclusive. \p n = number of values to generate. */
template <typename Container_t,
          typename std::enable_if_t<
              std::is_integral_v<typename Container_t::value_type>,
              int> = 0>
auto random_values(std::size_t n,
                   typename Container_t::value_type lower_bound,
                   typename Container_t::value_type upper_bound) -> Container_t
{
    auto result = Container_t{};
    for (auto i = 0uL; i < n; ++i)
        result.insert(std::end(result), gen_int_type(lower_bound, upper_bound));
    return result;
}

/// Generate a container of random values.
/** Container_t != array; value_type == float type.
 * Bounds are inclusive. \p n = number of values to generate. */
template <typename Container_t,
          typename std::enable_if_t<
              std::is_floating_point_v<typename Container_t::value_type>,
              int> = 0>
auto random_values(std::size_t n,
                   typename Container_t::value_type lower_bound,
                   typename Container_t::value_type upper_bound) -> Container_t
{
    auto result = Container_t{};
    for (auto i = 0uL; i < n; ++i) {
        result.insert(std::end(result),
                      gen_float_type(lower_bound, upper_bound));
    }
    return result;
}

/// Generate a container of random values.
/** Container_t == array type; value_type == integral type.
 *  Bounds are inclusive. Fills entire array with random values. */
template <typename Container_t,
          typename std::enable_if_t<
              detail::is_std_array<Container_t>::value &&
                  std::is_integral_v<typename Container_t::value_type>,
              int> = 0>
auto random_values(typename Container_t::value_type lower_bound,
                   typename Container_t::value_type upper_bound) -> Container_t
{
    auto result = Container_t{};
    for (auto i = 0uL; i < std::tuple_size_v<Container_t>; ++i) {
        result[i] = gen_int_type(lower_bound, upper_bound);
    }
    return result;
}

/// Generate a container of random values.
/** Container_t == array type; value_type == float type.
 *  Bounds are inclusive. Fills entire array with random values. */
template <typename Container_t,
          typename std::enable_if_t<
              detail::is_std_array<Container_t>::value &&
                  std::is_floating_point_v<typename Container_t::value_type>,
              int> = 0>
auto random_values(typename Container_t::value_type lower_bound,
                   typename Container_t::value_type upper_bound) -> Container_t
{
    auto result = Container_t{};
    for (auto i = 0uL; i < std::tuple_size_v<Container_t>; ++i)
        result[i] = gen_float_type(lower_bound, upper_bound);
    return result;
}

}  // namespace utility
#endif  // UTILITIES_RANDOM_VALUE_HPP
