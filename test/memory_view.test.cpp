#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

#include <utility/memory_view.hpp>

TEST(MemoryView, IntegralValues)
{
    using namespace utility;
    const auto a = 765;
    EXPECT_EQ("0000 0000 0000 0000 0000 0010 1111 1101", as_binary(a));
    EXPECT_EQ("765", as_decimal(a));
    EXPECT_EQ("2 FD", as_hex(a));
    EXPECT_EQ("1375", as_octal(a));

    const auto b = std::numeric_limits<unsigned>::max();
    EXPECT_EQ("1111 1111 1111 1111 1111 1111 1111 1111", as_binary(b));
    EXPECT_EQ("4,294,967,295", as_decimal(b));
    EXPECT_EQ("FF FF FF FF", as_hex(b));
    EXPECT_EQ("37777777777", as_octal(b));

    const auto c = 0;
    EXPECT_EQ("0000 0000 0000 0000 0000 0000 0000 0000", as_binary(c));
    EXPECT_EQ("0", as_decimal(c));
    EXPECT_EQ("0", as_hex(c));
    EXPECT_EQ("0", as_octal(c));
}

TEST(MemoryView, 64BitStruct)
{
    using namespace utility;
    struct Foo {
        int a{7654};
        char b{'u'};
        std::int8_t c{17};
    };

    auto f = Foo{};

    EXPECT_EQ(
        "0000 0000 0000 0000 0001 0001 0111 0101 0000 0000 0000 0000 0001 1101 "
        "1110 0110",
        as_binary(f));
    EXPECT_EQ("19,194,208,853,478", as_decimal(f));
    EXPECT_EQ("11 75 00 00 1D E6", as_hex(f));
    EXPECT_EQ("427240000016746", as_octal(f));
}
