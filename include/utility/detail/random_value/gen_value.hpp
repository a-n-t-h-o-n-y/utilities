#ifndef UTILITY_DETAIL_RANDOM_VALUE_GEN_VALUE_HPP
#define UTILITY_DETAIL_RANDOM_VALUE_GEN_VALUE_HPP
#include <random>

namespace utility {
namespace detail {
namespace random_value {

// Integral value generator, generates anything between [lb, ub].
static auto gen_int_type = [](auto lb, auto ub) {
    static auto seed = std::random_device{};
    static auto gen = std::mt19937{seed()};
    auto dist = std::uniform_int_distribution<decltype(lb)>{lb, ub};
    return dist(gen);
};

// Floating Point value generator, generates anything between [lb, ub].
static auto gen_float_type = [](auto lb, auto ub) {
    static auto seed = std::random_device{};
    static auto gen = std::mt19937{seed()};
    auto dist = std::uniform_real_distribution<decltype(lb)>{lb, ub};
    return dist(gen);
};

}  // namespace random_value
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_RANDOM_VALUE_GEN_VALUE_HPP
