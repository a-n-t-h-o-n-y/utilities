#include <string>

#include <gtest/gtest.h>

#include "../smf_call_counter.hpp"

using namespace utility;

class Foo {
   public:
    Foo() = delete;
    Foo(int i) : i_{i} {}
    Foo(const std::string& s) : s_{s} {}
    Foo(int i, const std::string& s) : i_{i}, s_{s} {}

    operator std::string() const { return "Hello"; }

    int get_int() const { return i_; }
    void set(int i) { i_ = i; }

    std::string get_string() const { return s_; }
    void set(const std::string& s) { s_ = s; }

   private:
    int i_{0};
    std::string s_{"Default"};
};
using FooCounter = SMF_call_counter<Foo>;

TEST(SMFCallCounter, Transparency) {
    // FooCounter Foo_1{};  // Should not compile.
    FooCounter Foo_2(5);
    EXPECT_EQ(5, Foo_2.get_int());
    EXPECT_EQ("Default", Foo_2.get_string());

    Foo_2.set(6);
    Foo_2.set("Hello");
    EXPECT_EQ(6, Foo_2.get_int());
    EXPECT_EQ("Hello", Foo_2.get_string());

    FooCounter Foo_3("Hello");
    EXPECT_EQ(0, Foo_3.get_int());
    EXPECT_EQ("Hello", Foo_3.get_string());

    FooCounter Foo_4(5, "Hello");
    EXPECT_EQ(5, Foo_4.get_int());
    EXPECT_EQ("Hello", Foo_4.get_string());

    FooCounter Foo_5{Foo_2};
    EXPECT_EQ(6, Foo_5.get_int());
    EXPECT_EQ("Hello", Foo_5.get_string());

    FooCounter Foo_6{std::move(Foo_2)};
    EXPECT_EQ(6, Foo_6.get_int());
    EXPECT_EQ("Hello", Foo_6.get_string());

    Foo_3 = Foo_4;
    EXPECT_EQ(5, Foo_3.get_int());
    EXPECT_EQ("Hello", Foo_3.get_string());

    Foo_5 = std::move(Foo_4);
    EXPECT_EQ(5, Foo_5.get_int());
    EXPECT_EQ("Hello", Foo_5.get_string());

    FooCounter::reset_counts();
    ASSERT_EQ(0, FooCounter::get_default_cstr_count());
    ASSERT_EQ(0, FooCounter::get_misc_cstr_count());
    ASSERT_EQ(0, FooCounter::get_copy_cstr_count());
    ASSERT_EQ(0, FooCounter::get_move_cstr_count());
    ASSERT_EQ(0, FooCounter::get_copy_assignment_count());
    ASSERT_EQ(0, FooCounter::get_move_assignment_count());
    ASSERT_EQ(0, FooCounter::get_destructor_count());
}

struct Bar {
    Bar() = default;
    Bar(int) {}
    Bar(const std::string&) {}
    Bar(int, const std::string&) {}
};
using BarCounter = SMF_call_counter<Bar>;

TEST(SMFCallCounter, GetCount) {
    // Default Constructor
    BarCounter Bar_1;
    BarCounter Bar_2;
    EXPECT_EQ(2, BarCounter::get_default_cstr_count());
    EXPECT_EQ(0, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(0, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(0, BarCounter::get_move_cstr_count());
    EXPECT_EQ(0, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(0, BarCounter::get_move_assignment_count());
    EXPECT_EQ(0, BarCounter::get_destructor_count());

    // Misc. Constructor
    BarCounter Bar_3{5};
    BarCounter Bar_4{"Hello"};
    BarCounter Bar_5{5, "Hello"};
    EXPECT_EQ(2, BarCounter::get_default_cstr_count());
    EXPECT_EQ(3, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(0, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(0, BarCounter::get_move_cstr_count());
    EXPECT_EQ(0, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(0, BarCounter::get_move_assignment_count());
    EXPECT_EQ(0, BarCounter::get_destructor_count());

    // Copy Constructor
    BarCounter Bar_6{Bar_3};
    EXPECT_EQ(2, BarCounter::get_default_cstr_count());
    EXPECT_EQ(3, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(1, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(0, BarCounter::get_move_cstr_count());
    EXPECT_EQ(0, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(0, BarCounter::get_move_assignment_count());
    EXPECT_EQ(0, BarCounter::get_destructor_count());

    // Move Constructor
    BarCounter Bar_7{std::move(Bar_3)};
    EXPECT_EQ(2, BarCounter::get_default_cstr_count());
    EXPECT_EQ(3, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(1, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(1, BarCounter::get_move_cstr_count());
    EXPECT_EQ(0, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(0, BarCounter::get_move_assignment_count());
    EXPECT_EQ(0, BarCounter::get_destructor_count());

    // Copy Assignment
    Bar_4 = Bar_5;
    Bar_4 = Bar_4;
    EXPECT_EQ(2, BarCounter::get_default_cstr_count());
    EXPECT_EQ(3, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(1, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(1, BarCounter::get_move_cstr_count());
    EXPECT_EQ(2, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(0, BarCounter::get_move_assignment_count());
    EXPECT_EQ(0, BarCounter::get_destructor_count());

    // Move Assignment
    Bar_4 = std::move(Bar_5);
    EXPECT_EQ(2, BarCounter::get_default_cstr_count());
    EXPECT_EQ(3, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(1, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(1, BarCounter::get_move_cstr_count());
    EXPECT_EQ(2, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(1, BarCounter::get_move_assignment_count());
    EXPECT_EQ(0, BarCounter::get_destructor_count());

    // Destructor
    auto Bar_up = std::make_unique<BarCounter>();
    Bar_up.reset();
    EXPECT_EQ(3, BarCounter::get_default_cstr_count());
    EXPECT_EQ(3, BarCounter::get_misc_cstr_count());
    EXPECT_EQ(1, BarCounter::get_copy_cstr_count());
    EXPECT_EQ(1, BarCounter::get_move_cstr_count());
    EXPECT_EQ(2, BarCounter::get_copy_assignment_count());
    EXPECT_EQ(1, BarCounter::get_move_assignment_count());
    EXPECT_EQ(1, BarCounter::get_destructor_count());

    BarCounter::reset_counts();
}
