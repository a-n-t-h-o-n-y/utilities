#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <utility/container_view.hpp>
#include <utility/from_file.hpp>

TEST(FromFile, DefaultWhiteSpaceDelimiters) {
    auto found = utility::from_file("../test/whitespace_values.txt");
    auto expected = std::vector<int>{123, 321, 234, 432, 543, 345, 654,
                                     456, 765, 567, 678, 876, 789, 987};
    EXPECT_EQ(found, expected);
}

TEST(FromFile, SemiColonOrGDelimiters) {
    auto found = utility::from_file("../test/semicolon_g_values.txt", ";G\n");
    auto expected = std::vector<int>{123, 321, 234, 432, 543, 345, 654,
                                     456, 765, 567, 678, 876, 789, 987};
    EXPECT_EQ(found, expected);
}

TEST(FromFile, String4Delimiters) {
    auto found = utility::from_file<std::vector<std::string>>(
        "../test/4_strings.txt", "4\n");
    auto expected = std::vector<std::string>{"123", "321", "235", "532", "553",
                                             "355", "655", "556", "765", "567",
                                             "678", "876", "789", "987"};
    EXPECT_EQ(found, expected);
}
