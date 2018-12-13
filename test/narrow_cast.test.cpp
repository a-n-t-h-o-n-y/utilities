#include <cstdint>

#include <gtest/gtest.h>

#include <utility/narrow_cast.hpp>

TEST(NarrowCast, General) {
    EXPECT_THROW(utility::narrow_cast<std::int8_t>(5'000), std::runtime_error);
    EXPECT_NO_THROW(utility::narrow_cast<std::int8_t>(50));
    // try {
    //     utility::narrow_cast<std::int8_t>(5'000);
    // } catch (const std::runtime_error& e) {
    //     std::cout << e.what() << std::endl;
    // }
}
