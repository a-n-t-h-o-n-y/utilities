#include <gtest/gtest.h>

#include <utility/property.hpp>

struct Foo {
    int i;
    char c;
    double d;
};

TEST(PropertyTest, Construction)
{
    utility::Property<int> var_1{5};
    EXPECT_EQ(5, var_1.get());

    utility::Property<int> var_2;
    EXPECT_EQ(0, var_2.get());

    // TODO
    // construction specialization from Property<> types to copy value_ member
    // utility::Property<int> var_3{var_2};
    // EXPECT_EQ(0, var_3.get());

    utility::Property<Foo> var_4{5, 'a', 4.3};
    EXPECT_EQ(5, var_4.get().i);
    EXPECT_EQ('a', var_4.get().c);
    EXPECT_EQ(4.3, var_4.get().d);

    // utility::Property<Foo> var_5{var_4};
    // EXPECT_EQ(5, var_5.get().i);
    // EXPECT_EQ('a', var_5.get().c);
    // EXPECT_EQ(4.3, var_5.get().d);
}

TEST(PropertyTest, SetMemberValueChanged) {}

TEST(PropertyTest, SetMemberSignalCall) {}

TEST(PropertyTest, OutputStreamOperator) {}

TEST(PropertyTest, InputStreamOperator) {}
