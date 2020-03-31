#ifndef UTILITY_DETAIL_ALLOCATION_HPP
#define UTILITY_DETAIL_ALLOCATION_HPP
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <new>
#include <ostream>

namespace utility {
namespace detail {

static auto total_allocs_   = std::uint64_t{0};
static auto total_deallocs_ = std::uint64_t{0};
static auto total_bytes_    = std::uint64_t{0};

void output_totals()
{
    stream_
        << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    stream_ << "Total Allocations:     " << total_allocs_ << '\n';
    stream_ << "Total Deallocations:   " << total_deallocs_ << '\n';
    stream_ << "Total Bytes Allocated: " << total_bytes_ << '\n';
}

static int register_atexit_{std::atexit(output_totals)};

void* generic_allocator(std::size_t bytes, std::ostream& os)
{
    void* p = std::malloc(bytes);
    if (p == nullptr) {
        os << "Allocation of " << bytes << " bytes failed.\n";
        throw std::bad_alloc();
    }
    os << "ALLOCATING " << std::setw(8) << bytes << " bytes at " << p << '\n';
    ++total_allocs_;
    total_bytes_ += bytes;
    return p;
}

void generic_deallocator(void* ptr, std::ostream& os)
{
    os << "DEALLOCATING" << std::setw(17) << " at " << ptr << '\n';
    std::free(ptr);
    ++total_deallocs_;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_ALLOCATION_HPP
