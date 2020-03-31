#ifndef UTILITY_DETAIL_NEW_OVERLOADS_HPP
#define UTILITY_DETAIL_NEW_OVERLOADS_HPP
#include <cstddef>
#include <cstdlib>

#include "allocation.hpp"

void* operator new(std::size_t bytes)
{
    return utility::detail::generic_allocator(bytes, utility::detail::stream_);
}

void* operator new[](std::size_t bytes)
{
    return utility::detail::generic_allocator(bytes, utility::detail::stream_);
}

void operator delete(void* ptr)
{
    return utility::detail::generic_deallocator(ptr, utility::detail::stream_);
}

void operator delete[](void* ptr)
{
    return utility::detail::generic_deallocator(ptr, utility::detail::stream_);
}

#endif  // UTILITY_DETAIL_NEW_OVERLOADS_HPP
