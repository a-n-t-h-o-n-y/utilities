#include <gtest/gtest.h>

#include <algorithm>
#include <climits>
#include <cstdint>

#include <utility/bit_array.hpp>

using namespace utility;

TEST(BitArray, DefaultConstruction)
{
    for (auto const x = Bit_array<int>{}; bool b : x)
        EXPECT_FALSE(b);

    for (auto const x = Bit_array<long[50]>{}; bool b : x)
        EXPECT_FALSE(b);
}

TEST(BitArray, InitListConstructor)
{
    {
        auto const x = Bit_array<short>{true, false, false, true};
        EXPECT_TRUE(x[0]);
        EXPECT_FALSE(x[1]);
        EXPECT_FALSE(x[2]);
        EXPECT_FALSE(x[15]);
    }
    {
        auto const x = Bit_array<int[4]>{true, false, true};
        EXPECT_TRUE(x[0]);
        EXPECT_FALSE(x[1]);
        EXPECT_TRUE(x[2]);
        EXPECT_FALSE(x[3]);
        EXPECT_FALSE(x[60]);
    }
}

TEST(BitArray, Size)
{
    {
        auto const x = Bit_array<int>{};
        EXPECT_EQ(4 * CHAR_BIT, x.size());
    }
    {
        auto const x = Bit_array<int[1024]>{};
        EXPECT_EQ(1024 * 4 * CHAR_BIT, x.size());
    }
    EXPECT_EQ(4 * CHAR_BIT, Bit_array<int>::size());
    EXPECT_EQ(256 * CHAR_BIT, Bit_array<char[256]>::size());
}

TEST(BitArray, Set)
{
    {
        auto x = Bit_array<char>{};
        for (auto i = 0uL; i < x.size(); ++i)
            x.set(i, true);
        for (bool b : x)
            EXPECT_TRUE(b);

        for (auto i = 0uL; i < x.size(); ++i)
            x.set(i, false);
        for (bool b : x)
            EXPECT_FALSE(b);
    }

    {
        auto x = Bit_array<unsigned char[512]>{};
        for (auto i = 0uL; i < x.size(); ++i)
            x.set(i, true);
        for (bool b : x)
            EXPECT_TRUE(b);

        for (auto i = 0uL; i < x.size(); ++i)
            x.set(i, false);
        for (bool b : x)
            EXPECT_FALSE(b);
    }
}

TEST(BitArray, At)
{
    {
        auto x = Bit_array<std::uint64_t>{true};
        for (auto i = 1uL; i < x.size(); ++i)
            x.set(i, !x.at(i - 1));

        auto foo = true;
        for (auto i = 0uL; i < x.size(); ++i) {
            EXPECT_EQ(foo, x.at(i));
            foo = !foo;
        }
        EXPECT_THROW(x.at(x.size()), std::out_of_range);
        EXPECT_THROW(x.at(x.size() + 1), std::out_of_range);
    }
    {
        auto x = Bit_array<std::uint64_t[16'384]>{true};
        for (auto i = 1uL; i < x.size(); ++i)
            x.set(i, !x.at(i - 1));

        auto foo = true;
        for (auto i = 0uL; i < x.size(); ++i) {
            EXPECT_EQ(foo, x.at(i));
            foo = !foo;
        }
        EXPECT_THROW(x.at(x.size()), std::out_of_range);
        EXPECT_THROW(x.at(x.size() + 1), std::out_of_range);
    }
}
