#include <utility>

#include <gtest/gtest.h>

#include <utility/smf_call_counter.hpp>

struct Bar {
    int a;
    double b;
    char c;
};

TEST(SMFCallCounterAggregate, Counts)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    {
        Baz var_1;                    // Default Constructor
        Baz var_2{1, 2.3, 'a'};       // Aggregate Direct Constructor
        Baz var_3{var_2};             // Copy Constructor
        Baz var_4{std::move(var_2)};  // Copy Constructor
        Baz var_5{Baz{3, 2.1, 'b'}};  // Aggregate Direct Cstr; Copy Elision
        var_1 = var_3;                // Copy Assignment
        var_3 = std::move(var_1);     // Copy Assignment
    }

    EXPECT_EQ(1, Baz::get_default_cstr_count());
    EXPECT_EQ(2, Baz::get_direct_cstr_counts());
    EXPECT_EQ(2, (Baz::get_direct_cstr_count<int, double, char>()));
    EXPECT_EQ(2, Baz::get_copy_cstr_count());
    EXPECT_EQ(2, Baz::get_copy_assignment_count());
    EXPECT_EQ(5, Baz::get_destructor_count());

    Baz::reset_counts();
    EXPECT_EQ(0, Baz::get_default_cstr_count());
    EXPECT_EQ(0, Baz::get_direct_cstr_counts());
    EXPECT_EQ(0, (Baz::get_direct_cstr_count<int, double, char>()));
    EXPECT_EQ(0, Baz::get_copy_cstr_count());
    EXPECT_EQ(0, Baz::get_copy_assignment_count());
    EXPECT_EQ(0, Baz::get_destructor_count());
}

TEST(SMFCallCounterAggregate, TranparentMemberAccess)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    Baz var{3, 2.1, 'a'};
    EXPECT_EQ(3, var.a);
    EXPECT_EQ(2.1, var.b);
    EXPECT_EQ('a', var.c);
}

TEST(SMFCallCounterAggregate, DefaultCstrStringOutput)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    Baz var_1;
    Baz var_2;
    EXPECT_EQ("Bar() called 2 times.", Baz::default_cstr_count_as_string());
}

TEST(SMFCallCounterAggregate, DirectCstrStringOutput)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    Baz var_1{5, 1.2, 'b'};
    Baz var_2{1, 2.5};
    EXPECT_EQ("Bar{int, double} called 1 times.",
              (Baz::direct_cstr_count_as_string<int, double>()));
    EXPECT_EQ("Bar{int, double, char} called 1 times.",
              (Baz::direct_cstr_count_as_string<int, double, char>()));
}

TEST(SMFCallCounterAggregate, CopyCstrStringOutput)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    Baz var_1;
    Baz var_2 = var_1;
    Baz var_3{var_1};
    Baz var_4(var_3);
    EXPECT_EQ("Bar(const Bar&) called 3 times.",
              Baz::copy_cstr_count_as_string());
}

TEST(SMFCallCounterAggregate, CopyAssignmentStringOutput)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    Baz var_1;
    Baz var_2;
    var_1 = var_2;
    var_2 = var_2;
    var_2 = var_1;
    EXPECT_EQ("Bar& operator=(const Bar&) called 3 times.",
              Baz::copy_assignment_count_as_string());
}

TEST(SMFCallCounterAggregate, DestructorStringOutput)
{
    using Baz = utility::SMF_call_counter<Bar>;
    Baz::reset_counts();
    {
        Baz var_1;
        Baz var_2;
        Baz var_3;
        Baz var_4;
    }
    EXPECT_EQ("~Bar() called 4 times.", Baz::destructor_count_as_string());
}
