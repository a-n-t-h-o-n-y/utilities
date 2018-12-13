#include <type_traits>

#include <gtest/gtest.h>

#include <utility/compound_trait.hpp>
#include <utility/trait_conjunction.hpp>

struct Foo {};
struct Bar {};

template <typename Type>
using Is_const_class =
    utility::Compound_trait<std::is_class, std::is_const>::template type<Type>;

template <typename... Types>
using Are_const_classes = utility::Trait_conjunction<Is_const_class, Types...>;

TEST(CompoundTrait, Default) {
    EXPECT_FALSE(Is_const_class<int>::value);
    EXPECT_FALSE(Is_const_class<const int>::value);
    EXPECT_TRUE(Is_const_class<const Foo>::value);

    // Works with Trait Conjunction
    EXPECT_TRUE(
        (utility::trait_conjunction_v<Is_const_class, const Foo, const Bar>));
    EXPECT_FALSE((utility::trait_conjunction_v<Is_const_class, const Foo,
                                               const Bar, int, double>));

    EXPECT_TRUE((Are_const_classes<const Foo, const Bar>::value));
    EXPECT_FALSE((Are_const_classes<const Foo, const Bar, int, double>::value));
}
