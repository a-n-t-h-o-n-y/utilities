#include <memory>
#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "../smf_call_counter.hpp"

TEST(SMFCallCounterClass, UniquePtr) {
    using Unique_ptr = utility::SMF_call_counter<std::unique_ptr<int>>;
    Unique_ptr::reset_counts();
    Unique_ptr var_1;                            // Default constructor
    Unique_ptr var_2{std::make_unique<int>(1)};  // Move constructor
    Unique_ptr var_3{std::move(var_2)};          // Move constructor
    var_1 = std::move(var_3);                    // Move assignment

    EXPECT_EQ(1, Unique_ptr::get_default_cstr_count());
    EXPECT_EQ(0, Unique_ptr::get_direct_cstr_counts());
    EXPECT_EQ(0, Unique_ptr::get_direct_cstr_count<std::unique_ptr<int>>());
    EXPECT_EQ(0, Unique_ptr::get_copy_cstr_count());
    EXPECT_EQ(2, Unique_ptr::get_move_cstr_count());
    EXPECT_EQ(0, Unique_ptr::get_assignment_counts());
    EXPECT_EQ(0, Unique_ptr::get_copy_assignment_count());
    EXPECT_EQ(1, Unique_ptr::get_move_assignment_count());
    EXPECT_EQ(0, Unique_ptr::get_destructor_count());
}

// Non-Trivial Type
struct Foo {
    Foo() {}
    Foo(int, double) {}
    Foo(const std::string&) {}
    Foo(const Foo&) {}
    Foo(Foo&&) {}
    Foo& operator=(const Foo&) = default;
    Foo& operator=(Foo&&) = default;
    int operator=(bool) { return 5; }
};

TEST(SMFCallCounterClass, NonTrivialType) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;                      // Foo()
    Foobar var_2{1, 2.3};              // Foo(int, double)
    Foobar var_25{1, 2.3};             // Foo(int, double)
    Foobar var_3{std::string{"abc"}};  // Foo(std::string)
    var_1 = var_2;                     // Copy Assignment
    Foobar var_4{std::move(var_1)};    // Move Constructor
    var_2 = std::move(var_3);          // Move Assignment
    Foobar var_5{Foo{}};               // Move Constructor
    Foobar var_6{"abc"};               // Foo(const char[4])
    Foobar var_7(7.6f, 5);             // Foo(int, double)
    Foobar var_8{var_7};               // Copy Construction
    { Foobar var_9; }                  // Foo(); ~Foo();
    int i = var_7 = true;              // Misc. Assignment Operator
    EXPECT_EQ(5, i);                   // Transparent Misc. operator=(U)

    EXPECT_EQ(2, Foobar::get_default_cstr_count());
    EXPECT_EQ(5, Foobar::get_direct_cstr_counts());
    EXPECT_EQ(2, (Foobar::get_direct_cstr_count<int, double>()));
    EXPECT_EQ(1, (Foobar::get_direct_cstr_count<float, int>()));
    EXPECT_EQ(1, Foobar::get_direct_cstr_count<std::string>());
    EXPECT_EQ(1, Foobar::get_direct_cstr_count<const char(&)[4]>());
    EXPECT_EQ(1, Foobar::get_copy_cstr_count());
    EXPECT_EQ(2, Foobar::get_move_cstr_count());
    EXPECT_EQ(1, Foobar::get_assignment_counts());
    EXPECT_EQ(1, Foobar::get_assignment_count<bool>());
    EXPECT_EQ(1, Foobar::get_copy_assignment_count());
    EXPECT_EQ(1, Foobar::get_move_assignment_count());
    EXPECT_EQ(1, Foobar::get_destructor_count());

    Foobar::reset_counts();
    EXPECT_EQ(0, Foobar::get_default_cstr_count());
    EXPECT_EQ(0, Foobar::get_direct_cstr_counts());
    EXPECT_EQ(0, (Foobar::get_direct_cstr_count<int, double>()));
    EXPECT_EQ(0, (Foobar::get_direct_cstr_count<float, int>()));
    EXPECT_EQ(0, Foobar::get_direct_cstr_count<std::string>());
    EXPECT_EQ(0, Foobar::get_direct_cstr_count<const char(&)[4]>());
    EXPECT_EQ(0, Foobar::get_copy_cstr_count());
    EXPECT_EQ(0, Foobar::get_move_cstr_count());
    EXPECT_EQ(0, Foobar::get_assignment_counts());
    EXPECT_EQ(0, Foobar::get_assignment_count<bool>());
    EXPECT_EQ(0, Foobar::get_copy_assignment_count());
    EXPECT_EQ(0, Foobar::get_move_assignment_count());
    EXPECT_EQ(0, Foobar::get_destructor_count());
}

// const T types do not work, copy cstr: SMF(T&) and SMF(const T&) ambiguity
// TEST(SMFCallCounterClass, ConstNonTrivialType) {
//     using Foobar = utility::SMF_call_counter<const Foo>;
//     Foobar::reset_counts();
//     Foobar var_1;                      // Foo()
//     Foobar var_2{1, 2.3};              // Foo(int, double)
//     Foobar var_25{1, 2.3};             // Foo(int, double)
//     Foobar var_3{std::string{"abc"}};  // Foo(std::string)
//     Foobar var_4{std::move(var_1)};    // Move Constructor
//     Foobar var_5{Foo{}};               // Move Constructor
//     Foobar var_6{"abc"};               // Foo(const char[4])
//     Foobar var_7(7.6f, 5);             // Foo(int, double)
//     Foobar var_8{var_7};               // Copy Construction
//     { Foobar var_9; }                  // Foo(); ~Foo();

//     EXPECT_EQ(2, Foobar::get_default_cstr_count());
//     EXPECT_EQ(5, Foobar::get_direct_cstr_counts());
//     EXPECT_EQ(2, (Foobar::get_direct_cstr_count<int, double>()));
//     EXPECT_EQ(1, (Foobar::get_direct_cstr_count<float, int>()));
//     EXPECT_EQ(1, Foobar::get_direct_cstr_count<std::string>());
//     EXPECT_EQ(1, Foobar::get_direct_cstr_count<const char(&)[4]>());
//     EXPECT_EQ(1, Foobar::get_copy_cstr_count());
//     EXPECT_EQ(2, Foobar::get_move_cstr_count());
//     EXPECT_EQ(0, Foobar::get_assignment_counts());
//     EXPECT_EQ(0, Foobar::get_assignment_count<bool>());
//     EXPECT_EQ(0, Foobar::get_copy_assignment_count());
//     EXPECT_EQ(0, Foobar::get_move_assignment_count());
//     EXPECT_EQ(1, Foobar::get_destructor_count());

//     Foobar::reset_counts();
//     EXPECT_EQ(0, Foobar::get_default_cstr_count());
//     EXPECT_EQ(0, Foobar::get_direct_cstr_counts());
//     EXPECT_EQ(0, (Foobar::get_direct_cstr_count<int, double>()));
//     EXPECT_EQ(0, (Foobar::get_direct_cstr_count<float, int>()));
//     EXPECT_EQ(0, Foobar::get_direct_cstr_count<std::string>());
//     EXPECT_EQ(0, Foobar::get_direct_cstr_count<const char(&)[4]>());
//     EXPECT_EQ(0, Foobar::get_copy_cstr_count());
//     EXPECT_EQ(0, Foobar::get_move_cstr_count());
//     EXPECT_EQ(0, Foobar::get_assignment_counts());
//     EXPECT_EQ(0, Foobar::get_assignment_count<bool>());
//     EXPECT_EQ(0, Foobar::get_copy_assignment_count());
//     EXPECT_EQ(0, Foobar::get_move_assignment_count());
//     EXPECT_EQ(0, Foobar::get_destructor_count());
// }

TEST(SMFCallCounterClass, TranparentClassWrapper) {
    using Unique_ptr = utility::SMF_call_counter<std::unique_ptr<int>>;
    Unique_ptr::reset_counts();
    Unique_ptr var{std::make_unique<int>(5)};
    var.reset();  // Type T transparency through SMF_call_counter<T>
    EXPECT_EQ(nullptr, var.get());
}

TEST(SMFCallCounterClass, DefaultCstrStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;
    Foobar var_2;
    EXPECT_EQ("Foo() called 2 times.", Foobar::default_cstr_count_as_string());
}

TEST(SMFCallCounterClass, DirectCstrStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1{5, 1.2};
    Foobar var_2{1, 2.5};
    EXPECT_EQ("Foo{int, double} called 2 times.",
              (Foobar::direct_cstr_count_as_string<int, double>()));
    EXPECT_EQ("Foo{int, double} called 2 times.",
              Foobar::direct_cstr_counts_as_string());
}

TEST(SMFCallCounterClass, CopyCstrStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;
    Foobar var_2 = var_1;
    Foobar var_3{var_1};
    Foobar var_4(var_3);
    EXPECT_EQ("Foo(const Foo&) called 3 times.",
              Foobar::copy_cstr_count_as_string());
}

TEST(SMFCallCounterClass, MoveCstrStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;
    Foobar var_2 = std::move(var_1);
    Foobar var_3{std::move(var_2)};
    Foobar var_4(std::move(var_3));
    EXPECT_EQ("Foo(Foo&&) called 3 times.",
              Foobar::move_cstr_count_as_string());
}

TEST(SMFCallCounterClass, CopyAssignmentStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;
    Foobar var_2;
    var_1 = var_2;
    var_2 = var_2;
    var_2 = var_1;
    EXPECT_EQ("Foo& operator=(const Foo&) called 3 times.",
              Foobar::copy_assignment_count_as_string());
}

TEST(SMFCallCounterClass, MoveAssignmentStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;
    Foobar var_2;
    var_1 = std::move(var_2);
    var_2 = std::move(var_1);
    var_1 = Foobar();
    EXPECT_EQ("Foo& operator=(Foo&&) called 3 times.",
              Foobar::move_assignment_count_as_string());
}

TEST(SMFCallCounterClass, AssignmentStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    Foobar var_1;
    var_1 = true;
    var_1 = false;
    var_1 = false;
    EXPECT_EQ("Foo::operator=(bool) called 3 times.",
              Foobar::assignment_counts_as_string());
    EXPECT_EQ("Foo::operator=(bool) called 3 times.",
              Foobar::assignment_count_as_string<bool>());
}

TEST(SMFCallCounterClass, DestructorStringOutput) {
    using Foobar = utility::SMF_call_counter<Foo>;
    Foobar::reset_counts();
    {
        Foobar var_1;
        Foobar var_2;
        Foobar var_3;
        Foobar var_4;
    }
    EXPECT_EQ("~Foo() called 4 times.", Foobar::destructor_count_as_string());
}
