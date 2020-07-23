#include <string>
#include <type_traits>

#include <utility/trait_disjunction.hpp>

#include <gtest/gtest.h>

struct Foo {};

struct Bar {};

struct Baz {};

TEST(TypeDisjunction, IsClass)
{
    {
        using TD = utility::Trait_disjunction<std::is_class, int, double, Foo>;
        EXPECT_TRUE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_class, Baz, Bar, Foo>;
        EXPECT_TRUE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_class, Baz>;
        EXPECT_TRUE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_class, int>;
        EXPECT_FALSE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_class, int, double, char,
                                              char, double>;
        EXPECT_FALSE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_class, int, bool, double,
                                              char, int, float, std::string>;
        EXPECT_TRUE(TD::value);
    }
}

TEST(TypeDisjunction, IsVoid)
{
    {
        using TD = utility::Trait_disjunction<std::is_void, void>;
        EXPECT_TRUE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_void, void, void, void,
                                              void, void>;
        EXPECT_TRUE(TD::value);
    }

    {
        using TD =
            utility::Trait_disjunction<std::is_void, int, char, double, float>;
        EXPECT_FALSE(TD::value);
    }

    {
        using TD = utility::Trait_disjunction<std::is_void, void, void, int,
                                              void, void>;
        EXPECT_TRUE(TD::value);
    }
}

template <typename... Types>
constexpr bool has_class()
{
    return utility::trait_disjunction_v<std::is_class, Types...>;
}

TEST(TypeDisjunction, HelperValue)
{
    {
        constexpr bool var =
            utility::trait_disjunction_v<std::is_void, void, void, int, void,
                                         void>;
        EXPECT_TRUE(var);
    }

    {
        constexpr bool var =
            utility::trait_disjunction_v<std::is_class, int, double, char>;
        EXPECT_FALSE(var);
    }

    {
        constexpr bool var = has_class<Foo, Bar>();
        EXPECT_TRUE(var);
    }

    {
        constexpr bool var = has_class<double, int>();
        EXPECT_FALSE(var);
    }
}
