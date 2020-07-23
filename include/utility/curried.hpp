#ifndef UTILITY_CURRIED_HPP
#define UTILITY_CURRIED_HPP
#include <tuple>
#include <type_traits>
#include <utility>

namespace utility {

/// Creates a curried function that can bind a variable number of arguments.
template <typename F, typename... CapturedArgs>
class Curried {
   private:
    F func_;
    std::tuple<CapturedArgs...> captured_;

   public:
    Curried(F function, CapturedArgs... args)
        : func_{function}, captured_{capture_by_copy(std::move(args)...)}
    {}

    Curried(F function, std::tuple<CapturedArgs...> args)
        : func_{function}, captured_{std::move(args)}
    {}

   public:
    template <typename... NewArgs>
    auto operator()(NewArgs&&... args) const
    {
        auto new_args = capture_by_copy(std::forward<NewArgs>(args)...);
        auto all_args = std::tuple_cat(captured_, std::move(new_args));
        if constexpr (std::is_invocable_v<F, CapturedArgs..., NewArgs...>)
            return std::apply(func_, std::move(all_args));
        else
            return Curried<F, CapturedArgs..., NewArgs...>{func_,
                                                           std::move(all_args)};
    }

   private:
    template <typename... Args>
    static auto capture_by_copy(Args&&... args)
    {
        return std::tuple<std::decay_t<Args>...>{std::forward<Args>(args)...};
    }
};

}  // namespace utility

// Catch2 Tests
// #include <catch2/catch.hpp>

// #include <halg.hpp>

// auto foo(int a, int b, int c) { return a + b + c; }

// TEST_CASE("Function Pointer", "[Curried]")
// {
//     using namespace halg;

//     auto foo_cd = detail::Curried{&foo};
//     auto foo_0  = foo_cd(4);
//     auto foo_1  = foo_0(7);
//     auto foo_2  = foo_1(5);

//     REQUIRE(foo_2 == 16);
//     REQUIRE(foo_0(7, 5) == 16);
//     REQUIRE(foo_1(5) == 16);
// }

// TEST_CASE("Lambda", "[Curried]")
// {
//     using namespace halg;

//     auto lam = [](int i, char c) { return c + i; };

//     auto lam_cd = detail::Curried{lam};
//     auto lam_0  = lam_cd(4);
//     auto lam_1  = lam_0('a');

//     REQUIRE(lam_1 == 'a' + 4);
//     REQUIRE(lam_0('g') == 'g' + 4);
// }

// template <typename... Args>
// auto bar(Args&&... args) -> int
// {
//     return (0 + ... + args);
// }

// TEST_CASE("Variadic Template", "[Curried]")
// {
//     using namespace halg;

//     auto bar_cd = detail::Curried{&bar<int, int, char>};

//     auto bar_0 = bar_cd(1);
//     auto bar_1 = bar_0(2);
//     auto bar_2 = bar_1('a');

//     REQUIRE(bar_2 == (1 + 2 + 'a'));
//     REQUIRE(bar_1('a') == (1 + 2 + 'a'));
//     REQUIRE(bar_0(2, 'a') == (1 + 2 + 'a'));
// }

#endif  // UTILITY_CURRIED_HPP
