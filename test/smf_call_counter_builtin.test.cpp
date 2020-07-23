#include <utility>

#include <gtest/gtest.h>

#include <utility/smf_call_counter.hpp>

using namespace utility;

TEST(SMFCallCounterBuiltin, Int)
{
    using Integer = utility::SMF_call_counter<int>;
    Integer::reset_counts();
    {
        Integer var_1;                    // Default Constructor
        Integer var_2{1};                 // Copy Constructor
        Integer var_3{std::move(var_2)};  // Copy Constructor
        var_1 = var_3;                    // Copy Assignment
        var_3 = std::move(var_1);         // Copy Assignment
        Integer var_4{1.2f};              // Copy Constructor
    }

    EXPECT_EQ(1, Integer::get_default_cstr_count());
    EXPECT_EQ(3, Integer::get_copy_cstr_count());
    EXPECT_EQ(2, Integer::get_copy_assignment_count());
    EXPECT_EQ(4, Integer::get_destructor_count());

    Integer::reset_counts();
    EXPECT_EQ(0, Integer::get_default_cstr_count());
    EXPECT_EQ(0, Integer::get_copy_cstr_count());
    EXPECT_EQ(0, Integer::get_copy_assignment_count());
    EXPECT_EQ(0, Integer::get_destructor_count());
}

void zero(int& i) { i = 0; }

TEST(SMFCallCounterBuiltin, ConversionOperators)
{
    using Integer = utility::SMF_call_counter<int>;
    Integer::reset_counts();
    Integer var{7};
    EXPECT_EQ(var, 7);
    zero(var);
    EXPECT_EQ(0, var);
    int& i = var;
    i      = 4;
    EXPECT_EQ(4, var);
    const int& ci{var};
    EXPECT_EQ(4, ci);
}

TEST(SMFCallCounterBuiltin, DefaultCstrStringOutput)
{
    using Integer = utility::SMF_call_counter<int>;
    Integer::reset_counts();
    Integer var_1;
    Integer var_2;
    EXPECT_EQ("int() called 2 times.", Integer::default_cstr_count_as_string());
}

TEST(SMFCallCounterBuiltin, CopyCstrStringOutput)
{
    using Integer = utility::SMF_call_counter<int>;
    Integer::reset_counts();
    Integer var_1;
    Integer var_2 = var_1;
    Integer var_3{var_1};
    Integer var_4(var_3);
    EXPECT_EQ("int(const int&) called 3 times.",
              Integer::copy_cstr_count_as_string());
}

TEST(SMFCallCounterBuiltin, CopyAssignmentStringOutput)
{
    using Integer = utility::SMF_call_counter<int>;
    Integer::reset_counts();
    Integer var_1;
    Integer var_2;
    var_1 = var_2;
    var_2 = var_2;
    var_2 = var_1;
    EXPECT_EQ("int& operator=(const int&) called 3 times.",
              Integer::copy_assignment_count_as_string());
}

TEST(SMFCallCounterBuiltin, DestructorStringOutput)
{
    using Integer = utility::SMF_call_counter<int>;
    Integer::reset_counts();
    {
        Integer var_1;
        Integer var_2;
        Integer var_3;
        Integer var_4;
    }
    EXPECT_EQ("~int() called 4 times.", Integer::destructor_count_as_string());
}

void foo() {}

TEST(SMFCallCounterBuiltin, FunctionPointer)
{
    using FuncPtr = SMF_call_counter<void (*)()>;
    {
        FuncPtr func_ptr{&foo};
    }
    EXPECT_EQ(0, FuncPtr::get_default_cstr_count());
    EXPECT_EQ(1, FuncPtr::get_copy_cstr_count());
    EXPECT_EQ(0, FuncPtr::get_copy_assignment_count());
    EXPECT_EQ(1, FuncPtr::get_destructor_count());
}

TEST(SMFCallCounterBuiltin, Nullptr)
{
    using NullPtr = SMF_call_counter<decltype(nullptr)>;
    {
        NullPtr null_ptr{nullptr};
    }
    EXPECT_EQ(0, NullPtr::get_default_cstr_count());
    EXPECT_EQ(1, NullPtr::get_copy_cstr_count());
    EXPECT_EQ(0, NullPtr::get_copy_assignment_count());
    EXPECT_EQ(1, NullPtr::get_destructor_count());
}

enum Color { Red, Blue, Green };

TEST(SMFCallCounterBuiltin, Enum)
{
    using ColorEnum = SMF_call_counter<Color>;
    {
        ColorEnum color_enum_1{Color::Red};
        ColorEnum color_enum_2;
    }
    EXPECT_EQ(1, ColorEnum::get_default_cstr_count());
    EXPECT_EQ(1, ColorEnum::get_copy_cstr_count());
    EXPECT_EQ(0, ColorEnum::get_copy_assignment_count());
    EXPECT_EQ(2, ColorEnum::get_destructor_count());
}
