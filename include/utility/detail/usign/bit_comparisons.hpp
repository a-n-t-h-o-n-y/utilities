#ifndef UTILITY_DETAIL_USIGN_BIT_COMPARISONS_HPP
#define UTILITY_DETAIL_USIGN_BIT_COMPARISONS_HPP
#include <bitset>
#include <cstddef>

namespace utility {
namespace detail {
namespace usign {

template <std::size_t N>
bool operator<(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
    if (N == 0) {
        return false;
    }
    for (auto i = N - 1; i < N; --i) {
        if (lhs[i] != rhs[i]) {
            return rhs[i];
        }
    }
    return false;
}

template <std::size_t N>
bool operator<=(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
    return lhs < rhs || lhs == rhs;
}

template <std::size_t N>
bool operator>(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
    return !(lhs <= rhs);
}

template <std::size_t N>
bool operator>=(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
    return lhs > rhs || lhs == rhs;
}

}  // namespace usign
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_USIGN_BIT_COMPARISONS_HPP
