#ifndef UTILITY_DETAIL_MEMORY_VIEW_BIT_AT_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_BIT_AT_HPP
#include <cstddef>

namespace utility::detail::memory_view {

// \p i is bit index into \p address.
auto bit_at(unsigned char const* address, std::size_t i) -> bool
{
    return address[i / 8] >> (i % 8) & 0x01 ? true : false;
}

}  // namespace utility::detail::memory_view
#endif  // UTILITY_DETAIL_MEMORY_VIEW_BIT_AT_HPP
