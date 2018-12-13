#ifndef UTILITY_DETAIL_MEMORY_VIEW_BIT_AT_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_BIT_AT_HPP
#include <cstddef>

namespace utility {
namespace detail {
namespace memory_view {

// \p i is bit index into \p address.
bool bit_at(const unsigned char* address, std::size_t i) {
    return address[i / 8] >> (i % 8) & 0x01 ? true : false;
}

}  // namespace memory_view
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_MEMORY_VIEW_BIT_AT_HPP
