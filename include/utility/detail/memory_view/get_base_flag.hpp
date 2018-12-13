#ifndef UTILITY_DETAIL_MEMORY_VIEW_GET_BASE_FLAG_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_GET_BASE_FLAG_HPP
#include <ios>

#include "representation.hpp"

namespace utility {
namespace detail {
namespace memory_view {

auto get_base_flag(Representation rep) {
    switch (rep) {
        case Representation::Decimal:
            return std::ios_base::dec;
        case Representation::Hex:
            return std::ios_base::hex;
        case Representation::Octal:
            return std::ios_base::oct;
        case Representation::Binary:
            return std::ios_base::fmtflags{};
    }
}

}  // namespace memory_view
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_MEMORY_VIEW_GET_BASE_FLAG_HPP
