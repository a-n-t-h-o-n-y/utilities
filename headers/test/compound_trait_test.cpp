#include <type_traits>

#include <gtest/gtest.h>

#include "../compound_trait.hpp"
#include "../trait_conjunction.hpp"

struct Foo {};
struct Bar {};

template <typename Type>
using is_const_class =
    utility::Compound_trait<std::is_class, std::is_const>::type<Type>;

template <typename... Types>
using are_const_classes = utility::Trait_conjunction<is_const_class, Types...>;

TEST(CompoundTrait, Default) {
    EXPECT_FALSE(is_const_class<int>::value);
    EXPECT_FALSE(is_const_class<const int>::value);
    EXPECT_TRUE(is_const_class<const Foo>::value);

    // Works with Trait Conjunction
    EXPECT_TRUE(
        (utility::trait_conjunction_v<is_const_class, const Foo, const Bar>));
    EXPECT_FALSE((utility::trait_conjunction_v<is_const_class, const Foo,
                                               const Bar, int, double>));

    EXPECT_TRUE((are_const_classes<const Foo, const Bar>::value));
    EXPECT_FALSE((are_const_classes<const Foo, const Bar, int, double>::value));
}
