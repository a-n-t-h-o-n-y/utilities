#ifndef UTILITIES_RANDOM_VALUE_HPP
#define UTILITIES_RANDOM_VALUE_HPP
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <type_traits>

namespace utility {
namespace detail {

template <typename>
struct is_std_array : std::false_type {};

template <typename T, std::size_t N>
struct is_std_array<std::array<T, N>> : std::true_type {};

// Integral value generator.
static auto gen_int_type = [](auto lb, auto ub) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<decltype(lb)> dist(lb, ub);
    return dist(gen);
};

// Floating Point value generator.
static auto gen_float_type = [](auto lb, auto ub) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<decltype(lb)> dist(lb, ub);
    return dist(gen);
};

}  // namespace detail
}  // namespace utility

namespace utility {

/// Generate a single integral type value.
template <
    typename Value_t,
    typename std::enable_if<std::is_integral<Value_t>::value, int>::type = 0>
Value_t random_value(Value_t lower_bound, Value_t upper_bound) {
    return detail::gen_int_type(lower_bound, upper_bound);
}

/// Generate a single random floating point type value.
template <typename Value_t,
          typename std::enable_if<std::is_floating_point<Value_t>::value,
                                  int>::type = 0>
Value_t random_value(Value_t lower_bound, Value_t upper_bound) {
    return detail::gen_float_type(static_cast<Value_t>(lower_bound),
                                  static_cast<Value_t>(upper_bound));
}

/// Generate a single random value - non-integral and non-floating point types.
/// Type must have a conversion from U.
template <typename Value_t,
          typename U,
          typename std::enable_if<!std::is_integral<Value_t>::value &&
                                      !std::is_floating_point<Value_t>::value,
                                  int>::type = 0>
Value_t random_value(const U& lower_bound, const U& upper_bound) {
    std::cout << typeid(Value_t).name() << std::endl;
    return static_cast<Value_t>(detail::gen_int_type(lower_bound, upper_bound));
}

/// Generate a container of random values.
/// Container_t != array; value_type == integral type.
template <typename Container_t,
          typename std::enable_if<
              std::is_integral<typename Container_t::value_type>::value,
              int>::type = 0>
Container_t random_values(std::size_t n,
                          typename Container_t::value_type lower_bound,
                          typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < n; ++i) {
        result.insert(std::end(result),
                      detail::gen_int_type(lower_bound, upper_bound));
    }
    return result;
}

/// Generate a container of random values.
/// Conatiner_t != array; value_type == float type.
template <typename Container_t,
          typename std::enable_if<
              std::is_floating_point<typename Container_t::value_type>::value,
              int>::type = 0>
Container_t random_values(std::size_t n,
                          typename Container_t::value_type lower_bound,
                          typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < n; ++i) {
        result.insert(std::end(result),
                      detail::gen_float_type(lower_bound, upper_bound));
    }
    return result;
}

/// Generate a container of random values.
/// Container_t == array type; value_type == integral type.
template <typename Container_t,
          typename std::enable_if<detail::is_std_array<Container_t>::value,
                                  int>::type = 0,
          typename std::enable_if<
              std::is_integral<typename Container_t::value_type>::value,
              int>::type = 0>
Container_t random_values(typename Container_t::value_type lower_bound,
                          typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < std::tuple_size<Container_t>::value; ++i) {
        result[i] = detail::gen_int_type(lower_bound, upper_bound);
    }
    return result;
}

/// Generate a container of random values.
/// Container_t == array type; value_type == float type.
template <typename Container_t,
          typename std::enable_if<detail::is_std_array<Container_t>::value,
                                  int>::type = 0,
          typename std::enable_if<
              std::is_floating_point<typename Container_t::value_type>::value,
              int>::type = 0>
Container_t random_values(typename Container_t::value_type lower_bound,
                          typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < std::tuple_size<Container_t>::value; ++i) {
        result[i] = detail::gen_float_type(lower_bound, upper_bound);
    }
    return result;
}

}  // namespace utility
#endif  // UTILITIES_RANDOM_VALUE_HPP
