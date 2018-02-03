#include <cstddef>
#include <stdexcept>
#include <vector>

#include <gtest/gtest.h>

#include "../strong_guarantee.hpp"

using Container_t = std::vector<int>;

template <typename Ret, typename... Args>
using Mem_fn_t = Ret (Container_t::*)(Args...);

TEST(StrongGuaranteeTest, Test) {
    Container_t v{5, 4, 3, 2, 1};

    utility::make_operation_strong(&Container_t::empty, v);

    using insert_type =
        Mem_fn_t<Container_t::iterator, Container_t::const_iterator,
                 Container_t::const_reference>;
    utility::make_operation_strong<insert_type>(&Container_t::insert, v,
                                                std::begin(v), 6);

    using at_type = Mem_fn_t<Container_t::reference, Container_t::size_type>;
    Container_t::reference value =
        utility::make_operation_strong<at_type>(&Container_t::at, v, 2);

    EXPECT_EQ(value, 4);
    EXPECT_EQ(v.at(2), 4);
    EXPECT_THROW(
        utility::make_operation_strong<at_type>(&Container_t::at, v, 9),
        std::out_of_range);
}
