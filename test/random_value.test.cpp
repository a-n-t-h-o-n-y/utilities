#include <algorithm>
#include <array>
#include <vector>

#include <gtest/gtest.h>

#include <utility/random_value.hpp>

namespace {
template <typename Number_t>
bool is_between(Number_t value, Number_t lb, Number_t ub)
{
    return value >= lb && value <= ub;
}

template <typename Container_t, typename Number_t>
bool is_between(const Container_t& values, Number_t lb, Number_t ub)
{
    return std::all_of(std::begin(values), std::end(values),
                       [lb, ub](auto a) { return is_between(a, lb, ub); });
}
}  // namespace

TEST(RandomValue, SingleValue)
{
    using utility::random_value;
    EXPECT_TRUE(is_between(random_value(0, 5), 0, 5));
    EXPECT_TRUE(is_between(random_value(543, 7000), 543, 7000));
    EXPECT_TRUE(is_between(random_value(0.5, 99.8), 0.5, 99.8));
    EXPECT_TRUE(is_between(random_value(5e9, 10e14), 5e9, 10e14));
}

TEST(RandomValue, VectorContainer)
{
    using utility::random_values;
    auto r1 = utility::random_values<std::vector<int>>(500, 50, 999);
    EXPECT_TRUE(is_between(r1, 50, 999));

    auto r2 = utility::random_values<std::vector<double>>(500, 9e4, 3e20);
    EXPECT_TRUE(is_between(r2, 9e4, 3e20));
}

TEST(RandomValue, ArrayContainer)
{
    using utility::random_values;
    auto r1 = utility::random_values<std::array<int, 500>>(50, 999);
    EXPECT_TRUE(is_between(r1, 50, 999));

    auto r2 = utility::random_values<std::array<double, 500>>(9e4, 3e20);
    EXPECT_TRUE(is_between(r2, 9e4, 3e20));
}
