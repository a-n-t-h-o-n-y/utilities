#include <chrono>
#include <cmath>
#include <thread>

#include <map>

#include <iostream>  // temp

#include <gtest/gtest.h>

#include <utility/async_trigger.hpp>

TEST(AsyncTrigger, Default) {
    const auto frame_time = std::chrono::microseconds(1);
    const auto test_time = std::chrono::seconds(5);

    auto sin_duration = [] {
        const double pi{std::atan(1.0) * 4.0};
        const double two_pi{2.0 * pi};
        static double i{0.0};
        const double depth{250.0};  // depth
        std::chrono::milliseconds result{0};
        if (i <= two_pi) {
            double relative_level{std::sin(i)};
            result = std::chrono::milliseconds(
                static_cast<long>(std::abs(relative_level * depth)));
            i += 0.2;  // period or rate
        } else {
            i = 0.0;
        }
        return result;
    };

    utility::Async_trigger at{frame_time};
    at.set_period(sin_duration);
    at.trigger.connect([] {
        static int x{0};
        std::cout << ++x << std::endl;
    });
    at.start();
    std::this_thread::sleep_for(test_time);
    at.stop();

    std::map<int, utility::Async_trigger> mp;
    mp[5] = std::move(utility::Async_trigger{std::chrono::milliseconds(5)});
}
