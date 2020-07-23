#include <gtest/gtest.h>

#include <utility/smf_call_counter.hpp>

using namespace utility;

TEST(SMFCallCounterArray, SMFCounts)
{
    using Array = utility::SMF_call_counter<int[5]>;
    Array::reset_counts();
    {
        Array var_1;                 // Default Constructor
        Array var_2{1, 2, 3, 4, 5};  // Initializer List Constructor
        Array var_3{1, 2, 3};        // Initializer List Constructor
        Array var_4{5, 4, 3, 2, 1};  // Initializer List Constructor
        Array var_5{};               // Default Constructor
    }
    EXPECT_EQ(2, Array::get_default_cstr_count());
    EXPECT_EQ(3, Array::get_initializer_list_cstr_count());
    EXPECT_EQ(5, Array::get_destructor_count());

    Array::reset_counts();
    EXPECT_EQ(0, Array::get_default_cstr_count());
    EXPECT_EQ(0, Array::get_initializer_list_cstr_count());
    EXPECT_EQ(0, Array::get_destructor_count());
}

TEST(SMFCallCounterArray, ConstIntArray)
{
    using Array = utility::SMF_call_counter<const int[5]>;
    Array::reset_counts();
    Array var{1, 2, 3, 4, 5};
    EXPECT_EQ(1, var[0]);
    EXPECT_EQ(5, var[4]);
    const int* p = var;
    EXPECT_EQ(1, p[0]);
}

TEST(SMFCallCounterArray, ConstCharArray)
{
    using Array = utility::SMF_call_counter<const char[6]>;
    Array::reset_counts();
    // Array var{"Hello"}; // Not possible to pass literal to non-aggregate memb
    Array var{'H', 'e', 'l', 'l', 'o', '\0'};
    EXPECT_EQ('H', var[0]);
    EXPECT_EQ('o', var[4]);
    EXPECT_EQ('\0', var[5]);
    const char* p = var;
    EXPECT_EQ('H', p[0]);
}

TEST(SMFCallCounterArray, AccessOperator)
{
    using Array = utility::SMF_call_counter<int[5]>;
    Array::reset_counts();
    Array var{1, 2, 3, 4, 5};
    EXPECT_EQ(1, var[0]);
    EXPECT_EQ(5, var[4]);

    int* p = var;
    ASSERT_NE(nullptr, p);
    EXPECT_EQ(1, p[0]);

    var[0] = 6;
    EXPECT_EQ(6, var[0]);
    EXPECT_EQ(6, *p);
}

TEST(SMFCallCounterArray, DefaultCstrStringOutput)
{
    using Array = utility::SMF_call_counter<int[5]>;
    Array::reset_counts();
    Array var_1;
    Array var_2;
    EXPECT_EQ("int [5]() called 2 times.",
              Array::default_cstr_count_as_string());
}

TEST(SMFCallCounterArray, InitializerListConstructorStringOutput)
{
    using Array = utility::SMF_call_counter<int[5]>;
    Array::reset_counts();
    Array var_1{1, 2, 3, 4, 5};
    Array var_2{5, 4, 3, 2, 1};
    EXPECT_EQ("int [5]{std::initializer_list<int>} called 2 times.",
              Array::initializer_list_cstr_count_as_string());
}

TEST(SMFCallCounterArray, DestructorStringOutput)
{
    using Array = utility::SMF_call_counter<int[5]>;
    Array::reset_counts();
    {
        Array var_1;
        Array var_2;
        Array var_3{1, 2, 3, 4, 5};
        Array var_4;
    }
    EXPECT_EQ("~int [5]() called 4 times.",
              Array::destructor_count_as_string());
}
