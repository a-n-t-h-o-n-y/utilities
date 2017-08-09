#ifndef GEN_RANDOM_DATA_HPP
#define GEN_RANDOM_DATA_HPP
#include <array>
#include <cstddef>
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

// Not array; value_type = integral type.
template <typename Container,
          typename std::enable_if<
              std::is_integral<typename Container::value_type>::value,
              int>::type = 0>
Container gen_random_data(std::size_t n,
                          typename Container::value_type lower_bound,
                          typename Container::value_type upper_bound) {
    Container result;
    for (std::size_t i{0}; i < n; ++i) {
        result.insert(std::end(result), gen_int_type(lower_bound, upper_bound));
    }
    return result;
}

// Not array; value_type = float type.
template <typename Container,
          typename std::enable_if<
              std::is_floating_point<typename Container::value_type>::value,
              int>::type = 0>
Container gen_random_data(std::size_t n,
                          typename Container::value_type lower_bound,
                          typename Container::value_type upper_bound) {
    Container result;
    for (std::size_t i{0}; i < n; ++i) {
        result.insert(std::end(result),
                      gen_float_type(lower_bound, upper_bound));
    }
    return result;
}

// std::array type; value_type = integral type.
template <
    typename Container,
    typename std::enable_if<is_std_array<Container>::value, int>::type = 0,
    typename std::enable_if<
        std::is_integral<typename Container::value_type>::value,
        int>::type = 0>
Container gen_random_data(typename Container::value_type lower_bound,
                          typename Container::value_type upper_bound) {
    Container result;
    for (std::size_t i{0}; i < std::tuple_size<Container>::value; ++i) {
        result[i] = gen_int_type(lower_bound, upper_bound);
    }
    return result;
}

// std::array type; value_type = float type.
template <
    typename Container,
    typename std::enable_if<is_std_array<Container>::value, int>::type = 0,
    typename std::enable_if<
        std::is_floating_point<typename Container::value_type>::value,
        int>::type = 0>
Container gen_random_data(typename Container::value_type lower_bound,
                          typename Container::value_type upper_bound) {
    Container result;
    for (std::size_t i{0}; i < std::tuple_size<Container>::value; ++i) {
        result[i] = gen_float_type(lower_bound, upper_bound);
    }
    return result;
}

#endif  // GEN_RANDOM_DATA_HPP
