#ifndef UTILITY_DETAIL_MEMORY_VIEW_GET_BASE_FLAG_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_GET_BASE_FLAG_HPP
#include <ios>

#include "representation.hpp"

namespace utility::detail::memory_view {

auto get_base_flag(Representation rep) -> std::ios_base::fmtflags
{
    switch (rep) {
        case Representation::Decimal: return std::ios_base::dec;
        case Representation::Hex: return std::ios_base::hex;
        case Representation::Octal: return std::ios_base::oct;
        case Representation::Binary: return std::ios_base::fmtflags{};
    }
}

}  // namespace utility::detail::memory_view
#endif  // UTILITY_DETAIL_MEMORY_VIEW_GET_BASE_FLAG_HPP
