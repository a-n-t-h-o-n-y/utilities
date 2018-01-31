#ifndef UTILITY_DETAIL_NEW_OVERLOADS_HPP
#define UTILITY_DETAIL_NEW_OVERLOADS_HPP
#include <cstddef>
#include <cstdlib>

#include "allocation.hpp"

void* operator new(std::size_t bytes) {
    return utility::detail::generic_allocator(bytes, stream);
}

void* operator new[](std::size_t bytes) {
    return utility::detail::generic_allocator(bytes, stream);
}

void operator delete(void* ptr) {
    return utility::detail::generic_deallocator(ptr, stream);
}

void operator delete[](void* ptr) {
    return utility::detail::generic_deallocator(ptr, stream);
}

#endif  // UTILITY_DETAIL_NEW_OVERLOADS_HPP
