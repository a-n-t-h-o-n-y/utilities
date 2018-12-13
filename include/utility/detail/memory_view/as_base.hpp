#ifndef UTILITY_DETAIL_MEMORY_VIEW_AS_BASE_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_AS_BASE_HPP
#include "memory_view_class.hpp"
#include "representation.hpp"

namespace utility {
namespace detail {
namespace memory_view {

template <Representation base, typename Value_t>
auto as_base(const Value_t& value, bool separators) {
    auto mv = Memory_view<Value_t>{value};
    mv.set_representation(base);
    mv.enable_separators(separators);
    return mv.str();
}

}  // namespace memory_view
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_MEMORY_VIEW_AS_BASE_HPP
