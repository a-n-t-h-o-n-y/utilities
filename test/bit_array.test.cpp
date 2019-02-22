#include <gtest/gtest.h>

#include <climits>
#include <cstdint>

#include <utility/bit_array.hpp>

using namespace utility;

TEST(BitArray, DefaultConstruction) {
    Bit_array<int> bai;
    for (bool b : bai) {
        EXPECT_FALSE(b);
    }

    Bit_array<long[50]> bala;
    for (bool b : bala) {
        EXPECT_FALSE(b);
    }
}

TEST(BitArray, InitListConstructor) {
    const Bit_array<short> bas{true, false, false, true};
    EXPECT_TRUE(bas[0]);
    EXPECT_FALSE(bas[1]);
    EXPECT_FALSE(bas[2]);
    EXPECT_FALSE(bas[15]);

    const Bit_array<int[4]> baia{true, false, true};
    EXPECT_TRUE(baia[0]);
    EXPECT_FALSE(baia[1]);
    EXPECT_TRUE(baia[2]);
    EXPECT_FALSE(baia[3]);
    EXPECT_FALSE(baia[60]);
}

TEST(BitArray, Size) {
    Bit_array<int> bai;
    Bit_array<int[1024]> baia;
    EXPECT_EQ(4 * CHAR_BIT, bai.size());
    EXPECT_EQ(1024 * 4 * CHAR_BIT, baia.size());
    EXPECT_EQ(4 * CHAR_BIT, Bit_array<int>::size());
    EXPECT_EQ(256 * CHAR_BIT, Bit_array<char[256]>::size());
}

TEST(BitArray, Set) {
    Bit_array<char> bac;
    for (decltype(bac)::Size_t i{0}; i < bac.size(); ++i) {
        bac.set(i, true);
    }
    for (bool b : bac) {
        EXPECT_TRUE(b);
    }
    for (decltype(bac)::Size_t i{0}; i < bac.size(); ++i) {
        bac.set(i, false);
    }
    for (bool b : bac) {
        EXPECT_FALSE(b);
    }

    Bit_array<unsigned char[512]> baba;
    for (decltype(baba)::Size_t i{0}; i < baba.size(); ++i) {
        baba.set(i, true);
    }
    for (bool b : baba) {
        EXPECT_TRUE(b);
    }
    for (decltype(baba)::Size_t i{0}; i < baba.size(); ++i) {
        baba.set(i, false);
    }
    for (bool b : baba) {
        EXPECT_FALSE(b);
    }
}

TEST(BitArray, At) {
    Bit_array<std::uint64_t> bau{true};
    for (decltype(bau)::Size_t i{1}; i < bau.size(); ++i) {
        bau.set(i, !bau.at(i - 1));
    }
    bool foo{true};
    for (decltype(bau)::Size_t i{0}; i < bau.size(); ++i) {
        EXPECT_EQ(foo, bau.at(i));
        foo = !foo;
    }

    EXPECT_THROW(bau.at(bau.size()), std::out_of_range);
    EXPECT_THROW(bau.at(bau.size() + 1), std::out_of_range);

    Bit_array<std::uint64_t[16'384]> baua{true};
    for (decltype(baua)::Size_t i{1}; i < baua.size(); ++i) {
        baua.set(i, !baua.at(i - 1));
    }
    foo = true;
    for (decltype(baua)::Size_t i{0}; i < baua.size(); ++i) {
        EXPECT_EQ(foo, baua.at(i));
        foo = !foo;
    }

    EXPECT_THROW(baua.at(baua.size()), std::out_of_range);
    EXPECT_THROW(baua.at(baua.size() + 1), std::out_of_range);
}
