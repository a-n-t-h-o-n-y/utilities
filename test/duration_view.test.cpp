#include <chrono>
#include <ratio>

#include <gtest/gtest.h>

#include <utility/duration_view.hpp>

namespace {
using Duration_t = std::chrono::duration<long, std::nano>;
}  // namespace

using utility::duration_view;

TEST(DurationView, SpecifiedUnitsSingular)
{
    Duration_t duration_nanosecond{1};
    Duration_t duration_microsecond{1'000};
    Duration_t duration_millisecond{1'000'000};
    Duration_t duration_second{1'000'000'000};
    Duration_t duration_minute{60'000'000'000};
    Duration_t duration_hour{3'600'000'000'000};

    EXPECT_EQ("1 nanosecond",
              duration_view<std::chrono::nanoseconds>(duration_nanosecond));

    EXPECT_EQ("1 microsecond",
              duration_view<std::chrono::microseconds>(duration_microsecond));

    EXPECT_EQ("1 millisecond",
              duration_view<std::chrono::milliseconds>(duration_millisecond));

    EXPECT_EQ("1 second", duration_view<std::chrono::seconds>(duration_second));

    EXPECT_EQ("1 minute", duration_view<std::chrono::minutes>(duration_minute));

    EXPECT_EQ("1 hour", duration_view<std::chrono::hours>(duration_hour));
}

TEST(DurationView, SpecifiedUnitsUnExact)
{
    Duration_t duration_microsecond{1'050};
    Duration_t duration_millisecond{1'500'000};
    Duration_t duration_second{1'000'050'000};
    Duration_t duration_minute{60'050'000'000};
    Duration_t duration_hour{3'600'050'000'000};

    EXPECT_EQ("1 microsecond",
              duration_view<std::chrono::microseconds>(duration_microsecond));

    EXPECT_EQ("1 millisecond",
              duration_view<std::chrono::milliseconds>(duration_millisecond));

    EXPECT_EQ("1 second", duration_view<std::chrono::seconds>(duration_second));

    EXPECT_EQ("1 minute", duration_view<std::chrono::minutes>(duration_minute));

    EXPECT_EQ("1 hour", duration_view<std::chrono::hours>(duration_hour));
}

TEST(DurationView, SpecifiedUnitsZero)
{
    Duration_t duration_nanosecond{0};
    Duration_t duration_microsecond{50};
    Duration_t duration_millisecond{500'000};
    Duration_t duration_second{50'000};
    Duration_t duration_minute{50'000'000};
    Duration_t duration_hour{600'050'000'000};

    EXPECT_EQ("0 nanoseconds",
              duration_view<std::chrono::nanoseconds>(duration_nanosecond));

    EXPECT_EQ("0 microseconds",
              duration_view<std::chrono::microseconds>(duration_microsecond));

    EXPECT_EQ("0 milliseconds",
              duration_view<std::chrono::milliseconds>(duration_millisecond));

    EXPECT_EQ("0 seconds",
              duration_view<std::chrono::seconds>(duration_second));

    EXPECT_EQ("0 minutes",
              duration_view<std::chrono::minutes>(duration_minute));

    EXPECT_EQ("0 hours", duration_view<std::chrono::hours>(duration_hour));
}

TEST(DurationView, SpecifiedUnitsPlural)
{
    Duration_t duration_nanosecond{5};
    Duration_t duration_microsecond{5'000};
    Duration_t duration_millisecond{5'000'000};
    Duration_t duration_second{5'000'000'000};
    Duration_t duration_minute{300'000'000'000};
    Duration_t duration_hour{18'000'000'000'000};

    EXPECT_EQ("5 nanoseconds",
              duration_view<std::chrono::nanoseconds>(duration_nanosecond));

    EXPECT_EQ("5 microseconds",
              duration_view<std::chrono::microseconds>(duration_microsecond));

    EXPECT_EQ("5 milliseconds",
              duration_view<std::chrono::milliseconds>(duration_millisecond));

    EXPECT_EQ("5 seconds",
              duration_view<std::chrono::seconds>(duration_second));

    EXPECT_EQ("5 minutes",
              duration_view<std::chrono::minutes>(duration_minute));

    EXPECT_EQ("5 hours", duration_view<std::chrono::hours>(duration_hour));
}

TEST(DurationView, SpecifiedUnitsWithSeperators)
{
    Duration_t duration_1{5'000'000'000'000};
    Duration_t duration_2{18'000'000'000'000'000};

    EXPECT_EQ("5,000,000,000,000 nanoseconds",
              duration_view<std::chrono::nanoseconds>(duration_1));

    EXPECT_EQ("5,000,000,000 microseconds",
              duration_view<std::chrono::microseconds>(duration_1));

    EXPECT_EQ("5,000,000 milliseconds",
              duration_view<std::chrono::milliseconds>(duration_1));

    EXPECT_EQ("5,000 seconds", duration_view<std::chrono::seconds>(duration_1));

    EXPECT_EQ("300,000 minutes",
              duration_view<std::chrono::minutes>(duration_2));

    EXPECT_EQ("5,000 hours", duration_view<std::chrono::hours>(duration_2));
}
TEST(DurationView, SpecifiedUnitsNoSeperators)
{
    Duration_t duration_1{5'000'000'000'000};
    Duration_t duration_2{18'000'000'000'000'000};

    EXPECT_EQ("5000000000000 nanoseconds",
              duration_view<std::chrono::nanoseconds>(duration_1, false));

    EXPECT_EQ("5000000000 microseconds",
              duration_view<std::chrono::microseconds>(duration_1, false));

    EXPECT_EQ("5000000 milliseconds",
              duration_view<std::chrono::milliseconds>(duration_1, false));

    EXPECT_EQ("5000 seconds",
              duration_view<std::chrono::seconds>(duration_1, false));

    EXPECT_EQ("300000 minutes",
              duration_view<std::chrono::minutes>(duration_2, false));

    EXPECT_EQ("5000 hours",
              duration_view<std::chrono::hours>(duration_2, false));
}

TEST(DurationView, SpecifiedDigits)
{
    // Long Duration
    Duration_t duration_long{18'000'000'000'000};
    EXPECT_EQ("18,000,000,000,000 nanoseconds",
              duration_view(duration_long, 16));
    EXPECT_EQ("18,000,000,000,000 nanoseconds",
              duration_view(duration_long, 15));
    EXPECT_EQ("18,000,000,000,000 nanoseconds",
              duration_view(duration_long, 14));
    EXPECT_EQ("18,000,000,000 microseconds", duration_view(duration_long, 13));
    EXPECT_EQ("18,000,000,000 microseconds", duration_view(duration_long, 12));
    EXPECT_EQ("18,000,000,000 microseconds", duration_view(duration_long, 11));
    EXPECT_EQ("18,000,000 milliseconds", duration_view(duration_long, 10));
    EXPECT_EQ("18,000,000 milliseconds", duration_view(duration_long, 9));
    EXPECT_EQ("18,000,000 milliseconds", duration_view(duration_long, 8));
    EXPECT_EQ("18,000 seconds", duration_view(duration_long, 7));
    EXPECT_EQ("18,000 seconds", duration_view(duration_long, 6));
    EXPECT_EQ("18,000 seconds", duration_view(duration_long, 5));
    EXPECT_EQ("300 minutes", duration_view(duration_long, 4));
    EXPECT_EQ("300 minutes", duration_view(duration_long, 3));
    EXPECT_EQ("5 hours", duration_view(duration_long, 2));
    EXPECT_EQ("5 hours", duration_view(duration_long, 1));
    EXPECT_EQ("5 hours", duration_view(duration_long, 0));

    // Short Duration
    Duration_t duration_short{5};
    EXPECT_EQ("0 microseconds", duration_view(duration_short, 0));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 1));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 2));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 3));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 4));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 5));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 6));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 7));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 8));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 9));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 10));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 11));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 12));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 13));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 14));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 15));
    EXPECT_EQ("5 nanoseconds", duration_view(duration_short, 16));
}

TEST(DurationView, SpecifiedDigitsNoSeperators)
{
    Duration_t duration_long{18'000'000'000'000};
    EXPECT_EQ("18000000000000 nanoseconds",
              duration_view(duration_long, 16, false));
    EXPECT_EQ("18000000000000 nanoseconds",
              duration_view(duration_long, 15, false));
    EXPECT_EQ("18000000000000 nanoseconds",
              duration_view(duration_long, 14, false));
    EXPECT_EQ("18000000000 microseconds",
              duration_view(duration_long, 13, false));
    EXPECT_EQ("18000000000 microseconds",
              duration_view(duration_long, 12, false));
    EXPECT_EQ("18000000000 microseconds",
              duration_view(duration_long, 11, false));
    EXPECT_EQ("18000000 milliseconds", duration_view(duration_long, 10, false));
    EXPECT_EQ("18000000 milliseconds", duration_view(duration_long, 9, false));
    EXPECT_EQ("18000000 milliseconds", duration_view(duration_long, 8, false));
    EXPECT_EQ("18000 seconds", duration_view(duration_long, 7, false));
    EXPECT_EQ("18000 seconds", duration_view(duration_long, 6, false));
    EXPECT_EQ("18000 seconds", duration_view(duration_long, 5, false));
    EXPECT_EQ("300 minutes", duration_view(duration_long, 4, false));
    EXPECT_EQ("300 minutes", duration_view(duration_long, 3, false));
    EXPECT_EQ("5 hours", duration_view(duration_long, 2, false));
    EXPECT_EQ("5 hours", duration_view(duration_long, 1, false));
    EXPECT_EQ("5 hours", duration_view(duration_long, 0, false));
}
