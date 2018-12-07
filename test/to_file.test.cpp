#include <vector>

#include <gtest/gtest.h>

#include <utility/from_file.hpp>
#include <utility/to_file.hpp>

TEST(ToFile, DefaultDelimiter) {
    auto values = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    utility::to_file(values, "values.txt");
    auto file_values = utility::from_file("values.txt");
    EXPECT_EQ(values, file_values);
}

TEST(ToFile, MultiDelimiter) {
    auto values = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    utility::to_file(values, "values.txt", ";G.");
    auto file_values = utility::from_file("values.txt", ";G.");
    EXPECT_EQ(values, file_values);
}
