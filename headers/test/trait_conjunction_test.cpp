#include <string>
#include <type_traits>

#include "../trait_conjunction.hpp"

#include <gtest/gtest.h>

struct Foo {};

struct Bar {};

struct Baz {};

TEST(TypeConjunction, IsClass) {
    using TC_1 = utility::Trait_conjunction<std::is_class, int, double, Foo>;
    EXPECT_FALSE(TC_1::value);

    using TC_2 = utility::Trait_conjunction<std::is_class, Baz, Bar, Foo>;
    EXPECT_TRUE(TC_2::value);

    using TC_3 = utility::Trait_conjunction<std::is_class, Baz>;
    EXPECT_TRUE(TC_3::value);

    using TC_4 = utility::Trait_conjunction<std::is_class, int>;
    EXPECT_FALSE(TC_4::value);

    using TC_5 = utility::Trait_conjunction<std::is_class, int, bool, double,
                                            char, int, float, std::string>;
    EXPECT_FALSE(TC_5::value);

    using TC_6 =
        utility::Trait_conjunction<std::is_class, TC_1, TC_2, TC_3, TC_4, TC_5>;
    EXPECT_TRUE(TC_6::value);

    using TC_7 = utility::Trait_conjunction<std::is_class, TC_1, TC_2, TC_3,
                                            TC_4, TC_5, int>;
    EXPECT_FALSE(TC_7::value);
}

TEST(TypeConjunction, IsVoid) {
    using TC_1 = utility::Trait_conjunction<std::is_void, void>;
    EXPECT_TRUE(TC_1::value);

    using TC_2 =
        utility::Trait_conjunction<std::is_void, void, void, void, void, void>;
    EXPECT_TRUE(TC_2::value);

    using TC_3 =
        utility::Trait_conjunction<std::is_void, int, void, void, void, void>;
    EXPECT_FALSE(TC_3::value);

    using TC_4 =
        utility::Trait_conjunction<std::is_void, void, void, int, void, void>;
    EXPECT_FALSE(TC_4::value);
}

TEST(TypeConjunction, HelperValue) {
    constexpr bool var_1 =
        utility::trait_conjunction_v<std::is_void, void, void, int, void, void>;
    EXPECT_FALSE(var_1);

    constexpr bool var_2 =
        utility::trait_conjunction_v<std::is_class, Foo, Bar, Baz>;
    EXPECT_TRUE(var_2);
}
