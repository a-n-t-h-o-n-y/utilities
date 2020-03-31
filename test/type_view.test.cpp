#include <iostream>

#include <gtest/gtest.h>

#include <utility/type_view.hpp>

TEST(type_view, Int)
{
    utility::type_view::primary_categories<int>(std::cout);
    utility::type_view::composite_categories<int>(std::cout);
    utility::type_view::type_properties<int>(std::cout);
    utility::type_view::operations<int, double>(std::cout);
    utility::type_view::property_queries<int>(std::cout);
    utility::type_view::type_relationships<int, double>(std::cout);
    utility::type_view::limits<int>(std::cout);
    utility::type_view_all<int>(std::cout);
}
