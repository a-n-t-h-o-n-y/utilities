#include <memory>
#include <string>
#include <typeinfo>

#include <gtest/gtest.h>

#include "../type_info.hpp"

class Foo {};

namespace bar {
void foobar(const int&, Foo&&) {}
struct Foo {};
}  // namespace bar

TEST(TypeInfo, ObjectType) {
    utility::Type_info info_1{utility::get_type_info<int>()};
    EXPECT_EQ("int", static_cast<std::string>(info_1));

    utility::Type_info info_2{utility::get_type_info<const int>()};
    EXPECT_EQ("const int", static_cast<std::string>(info_2));

    utility::Type_info info_3{utility::get_type_info<volatile int>()};
    EXPECT_EQ("volatile int", static_cast<std::string>(info_3));

    utility::Type_info info_4{utility::get_type_info<const volatile int>()};
    EXPECT_EQ("const volatile int", static_cast<std::string>(info_4));

    utility::Type_info info_5{utility::get_type_info<const volatile int&>()};
    EXPECT_EQ("const volatile int&", static_cast<std::string>(info_5));

    utility::Type_info info_6{utility::get_type_info<const volatile int&&>()};
    EXPECT_EQ("const volatile int&&", static_cast<std::string>(info_6));

    utility::Type_info info_7{utility::get_type_info<const Foo&>()};
    EXPECT_EQ("const Foo&", static_cast<std::string>(info_7));

    const double d{90};
    utility::Type_info info_8{utility::get_type_info<decltype(d)>()};
    EXPECT_EQ("const double", static_cast<std::string>(info_8));

    const double&& d_rval{std::move(d)};
    utility::Type_info info_9{utility::get_type_info<decltype(d_rval)>()};
    EXPECT_EQ("const double&&", static_cast<std::string>(info_9));

    utility::Type_info info_10{utility::get_type_info<void>()};
    EXPECT_EQ("void", static_cast<std::string>(info_10));

    utility::Type_info info_11{utility::get_type_info<decltype(nullptr)>()};
    EXPECT_EQ("decltype(nullptr)", static_cast<std::string>(info_11));

    utility::Type_info info_12{utility::get_type_info<decltype(typeid(int))>()};
    EXPECT_EQ("const std::type_info&", static_cast<std::string>(info_12));
}

TEST(TypeInfo, PointerType) {
    utility::Type_info info_1{utility::get_type_info<long*>()};
    EXPECT_EQ("long*", static_cast<std::string>(info_1));

    utility::Type_info info_2{utility::get_type_info<const long*>()};
    EXPECT_EQ("long const*", static_cast<std::string>(info_2));

    utility::Type_info info_3{utility::get_type_info<const long* const>()};
    EXPECT_EQ("long const* const", static_cast<std::string>(info_3));

    utility::Type_info info_4{utility::get_type_info<long* volatile const>()};
    EXPECT_EQ("long* const volatile", static_cast<std::string>(info_4));

    utility::Type_info info_5{utility::get_type_info<long**** const>()};
    EXPECT_EQ("long**** const", static_cast<std::string>(info_5));

    utility::Type_info info_6{
        utility::get_type_info<volatile long** const*** volatile* const>()};
    EXPECT_EQ("long volatile** const*** volatile* const",
              static_cast<std::string>(info_6));

    int i{500};
    int* const ip{&i};
    utility::Type_info info_7{utility::get_type_info<decltype(ip)>()};
    EXPECT_EQ("int* const", static_cast<std::string>(info_7));

    volatile int vi{70};
    volatile int* vip{&vi};
    utility::Type_info info_8{utility::get_type_info<decltype(vip)>()};
    EXPECT_EQ("int volatile*", static_cast<std::string>(info_8));

    volatile int* const* vipp{&vip};
    utility::Type_info info_9{utility::get_type_info<decltype(vipp)>()};
    EXPECT_EQ("int volatile* const*", static_cast<std::string>(info_9));

    utility::Type_info info_10{utility::get_type_info<int**&>()};
    EXPECT_EQ("int**&", static_cast<std::string>(info_10));

    utility::Type_info info_11{utility::get_type_info<int*&&>()};
    EXPECT_EQ("int*&&", static_cast<std::string>(info_11));

    utility::Type_info info_12{utility::get_type_info<int* const&&>()};
    EXPECT_EQ("int* const&&", static_cast<std::string>(info_12));
}

TEST(TypeInfo, FunctionPointerType) {
    using Func1_t = void (*)();
    utility::Type_info info_1{utility::get_type_info<Func1_t>()};
    EXPECT_EQ("void (*)()", static_cast<std::string>(info_1));

    using Func2_t = Foo (*)(int, long);
    utility::Type_info info_2{utility::get_type_info<Func2_t>()};
    EXPECT_EQ("Foo (*)(int, long)", static_cast<std::string>(info_2));

    using Func3_t = Func2_t (*)(int&&, const Foo&, volatile double);
    utility::Type_info info_3{utility::get_type_info<Func3_t>()};
    EXPECT_EQ("Foo (*(*)(int&&, Foo const&, double))(int, long)",
              static_cast<std::string>(info_3));

    using Func4_t = void (*const)(int);
    utility::Type_info info_4{utility::get_type_info<Func4_t>()};
    EXPECT_EQ("void (* const)(int)", static_cast<std::string>(info_4));

    using Func5_t = void (*volatile const&)(int);
    utility::Type_info info_5{utility::get_type_info<Func5_t>()};
    EXPECT_EQ("void (* const volatile&)(int)",
              static_cast<std::string>(info_5));

    using Func6_t = int (*volatile &&)(int);
    utility::Type_info info_6{utility::get_type_info<Func6_t>()};
    EXPECT_EQ("int (* volatile&&)(int)", static_cast<std::string>(info_6));

    using Func7_t = Func6_t (*const volatile&&)(Func2_t);
    utility::Type_info info_7{utility::get_type_info<Func7_t>()};
    EXPECT_EQ(
        "int (* volatile&& (* const volatile&&)(Foo (*)(int, long)))(int)",
        static_cast<std::string>(info_7));

    utility::Type_info info_8{utility::get_type_info<decltype(&bar::foobar)>()};
    EXPECT_EQ("void (*)(int const&, Foo&&)", static_cast<std::string>(info_8));

    utility::Type_info info_9{utility::get_type_info<decltype(bar::foobar)>()};
    EXPECT_EQ("void (int const&, Foo&&)", static_cast<std::string>(info_9));

    utility::Type_info info_10{utility::get_type_info<const Func2_t>()};
    EXPECT_EQ("Foo (* const)(int, long)", static_cast<std::string>(info_10));
}

TEST(TypeInfo, InNamespace) {
    utility::Type_info info_1{utility::get_type_info<const bar::Foo&>()};
    EXPECT_EQ("const bar::Foo&", static_cast<std::string>(info_1));
}
