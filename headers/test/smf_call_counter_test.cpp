#include <gtest/gtest.h>

#include "../smf_call_counter.hpp"

using namespace utility;

class Foo {
   public:
    Foo() = delete;
    Foo(int i) : i_{i} {}
    Foo(const std::string& s) : s_{s} {}

    int get() { return i_; }
    void set(int i) { i_ = i; }

   private:
    int i_{0};
    std::string s_{"Default"};
};

TEST(SMFCallCounter, Default) {
    using FooCounter = SMF_call_counter<Foo>;
    FooCounter Foo_counter(5);
    EXPECT_EQ(0, FooCounter::get_default_cstr_count());
    EXPECT_EQ(1, FooCounter::get_misc_cstr_count());
    EXPECT_EQ(0, FooCounter::get_copy_cstr_count());
    EXPECT_EQ(0, FooCounter::get_move_cstr_count());
    EXPECT_EQ(0, FooCounter::get_copy_assignment_count());
    EXPECT_EQ(0, FooCounter::get_move_assignment_count());
    EXPECT_EQ(0, FooCounter::get_destructor_count());

    FooCounter Foo_counter2("Hello");
    EXPECT_EQ(0, FooCounter::get_default_cstr_count());
    EXPECT_EQ(2, FooCounter::get_misc_cstr_count());
    EXPECT_EQ(0, FooCounter::get_copy_cstr_count());
    EXPECT_EQ(0, FooCounter::get_move_cstr_count());
    EXPECT_EQ(0, FooCounter::get_copy_assignment_count());
    EXPECT_EQ(0, FooCounter::get_move_assignment_count());
    EXPECT_EQ(0, FooCounter::get_destructor_count());
}
