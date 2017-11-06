#ifndef UTILITIES_GEN_RANDOM_DATA_HPP
#define UTILITIES_GEN_RANDOM_DATA_HPP
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <type_traits>

namespace {
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

}  // namespace

namespace utility {

/// Generate a single integral type value.
template <
    typename Value_t,
    typename std::enable_if<std::is_integral<Value_t>::value, int>::type = 0>
Value_t random_value(Value_t lower_bound, Value_t upper_bound) {
    return gen_int_type(lower_bound, upper_bound);
}

/// Generate a single random floating point type value.
template <typename Value_t,
          typename std::enable_if<std::is_floating_point<Value_t>::value,
                                  int>::type = 0>
Value_t random_value(Value_t lower_bound, Value_t upper_bound) {
    return gen_float_type(lower_bound, upper_bound);
}

/// Generate a single random value - non-integral and non-floating point types.
/// Type must have a conversion from int.
template <typename Value_t>
Value_t random_value(int lower_bound, int upper_bound) {
    return static_cast<Value_t>(gen_int_type(lower_bound, upper_bound));
}

/// Generate a container of random values.
/// Container_t != array; value_type == integral type.
template <typename Container_t,
          typename std::enable_if<
              std::is_integral<typename Container_t::value_type>::value,
              int>::type = 0>
Container_t gen_random_data(std::size_t n,
                            typename Container_t::value_type lower_bound,
                            typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < n; ++i) {
        result.insert(std::end(result), gen_int_type(lower_bound, upper_bound));
    }
    return result;
}

/// Generate a container of random values.
/// Conatiner_t != array; value_type == float type.
template <typename Container_t,
          typename std::enable_if<
              std::is_floating_point<typename Container_t::value_type>::value,
              int>::type = 0>
Container_t gen_random_data(std::size_t n,
                            typename Container_t::value_type lower_bound,
                            typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < n; ++i) {
        result.insert(std::end(result),
                      gen_float_type(lower_bound, upper_bound));
    }
    return result;
}

/// Generate a container of random values.
/// Container_t == array; value_type == integral type.
template <
    typename Container_t,
    typename std::enable_if<is_std_array<Container_t>::value, int>::type = 0,
    typename std::enable_if<
        std::is_integral<typename Container_t::value_type>::value,
        int>::type = 0>
Container_t gen_random_data(typename Container_t::value_type lower_bound,
                            typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < std::tuple_size<Container_t>::value; ++i) {
        result[i] = gen_int_type(lower_bound, upper_bound);
    }
    return result;
}

/// Generate a container of random values.
/// Container_t == array type; value_type == float type.
template <
    typename Container_t,
    typename std::enable_if<is_std_array<Container_t>::value, int>::type = 0,
    typename std::enable_if<
        std::is_floating_point<typename Container_t::value_type>::value,
        int>::type = 0>
Container_t gen_random_data(typename Container_t::value_type lower_bound,
                            typename Container_t::value_type upper_bound) {
    Container_t result;
    for (std::size_t i{0}; i < std::tuple_size<Container_t>::value; ++i) {
        result[i] = gen_float_type(lower_bound, upper_bound);
    }
    return result;
}

}  // namespace utility
#endif  // UTILITIES_GEN_RANDOM_DATA_HPP
