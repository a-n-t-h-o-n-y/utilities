#include <gtest/gtest.h>

#include <utility/thousands_seperator.hpp>

TEST(ThousandsSeperator, Integrals) {
    EXPECT_EQ("1,000", utility::thousands_seperator(1000));
    EXPECT_EQ("-12,345", utility::thousands_seperator(-12345));
    EXPECT_EQ("0", utility::thousands_seperator(0));
    EXPECT_EQ("12", utility::thousands_seperator(12));
    EXPECT_EQ("-12", utility::thousands_seperator(-12));
    EXPECT_EQ("987,654,321,987,654,321",
              utility::thousands_seperator(987'654'321'987'654'321));
}

TEST(ThousandsSeperator, Floats) {
    EXPECT_EQ("1,000.000000", utility::thousands_seperator(1000.00));
    EXPECT_EQ("-10,500.123457", utility::thousands_seperator(-10500.1234567));
    EXPECT_EQ("0.000000", utility::thousands_seperator(0.0));
    EXPECT_EQ("12.000000", utility::thousands_seperator(12.0));
    EXPECT_EQ("-12.000000", utility::thousands_seperator(-12.0));
    // sub-string of result because of 18 digit precision limit.
    EXPECT_EQ(
        "654,321,987,654,321.12",
        utility::thousands_seperator(654'321'987'654'321.123L).substr(0, 22));
}

TEST(ThousandsSeperator, Strings) {
    // Integrals
    EXPECT_EQ("1,000", utility::thousands_seperator(std::string{"1000"}));
    EXPECT_EQ("-12,000", utility::thousands_seperator(std::string{"-12000"}));
    EXPECT_EQ("0", utility::thousands_seperator(std::string{"0"}));
    EXPECT_EQ("12", utility::thousands_seperator(std::string{"12"}));
    EXPECT_EQ("-12", utility::thousands_seperator(std::string{"-12"}));
    EXPECT_EQ("-987,654,321,987,654,321",
              utility::thousands_seperator(std::string{"-987654321987654321"}));
    // Floats
    EXPECT_EQ("1,000.000000",
              utility::thousands_seperator(std::string{"1000.00"}));
    EXPECT_EQ("-10,500.123457",
              utility::thousands_seperator(std::string{"-10500.1234567"}));
    EXPECT_EQ("0.000000", utility::thousands_seperator(std::string{"0.0"}));
    EXPECT_EQ("12.123450",
              utility::thousands_seperator(std::string{"12.12345"}));
    EXPECT_EQ("-12.123450",
              utility::thousands_seperator(std::string{"-12.12345"}));
    EXPECT_EQ("654,321,987,654,321.12",
              utility::thousands_seperator(std::string{"654321987654321.123"})
                  .substr(0, 22));
}

TEST(ThousandsSeperator, ConstCharPtr) {
    // Integrals
    EXPECT_EQ("1,000", utility::thousands_seperator("1000"));
    EXPECT_EQ("-12,000", utility::thousands_seperator("-12000"));
    EXPECT_EQ("0", utility::thousands_seperator("0"));
    EXPECT_EQ("12", utility::thousands_seperator("12"));
    EXPECT_EQ("-12", utility::thousands_seperator("-12"));
    EXPECT_EQ("-987,654,321,987,654,321",
              utility::thousands_seperator("-987654321987654321"));
    // Floats
    EXPECT_EQ("1,000.000000", utility::thousands_seperator("1000.00"));
    EXPECT_EQ("-10,500.123457", utility::thousands_seperator("-10500.1234567"));
    EXPECT_EQ("0.000000", utility::thousands_seperator("0.0"));
    EXPECT_EQ("12.123450", utility::thousands_seperator("12.12345"));
    EXPECT_EQ("-12.123450", utility::thousands_seperator("-12.12345"));
    EXPECT_EQ(
        "654,321,987,654,321.12",
        utility::thousands_seperator("654321987654321.123").substr(0, 22));
}
