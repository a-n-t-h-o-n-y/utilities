#ifndef UTILITY_DETAIL_USIGN_BIT_COMPARISONS_HPP
#define UTILITY_DETAIL_USIGN_BIT_COMPARISONS_HPP
#include <bitset>
#include <cstddef>

namespace utility::detail::usign {

template <std::size_t N>
auto operator<(std::bitset<N> const& lhs, std::bitset<N> const& rhs) -> bool
{
    if (N == 0)
        return false;
    for (auto i = N - 1; i < N; --i) {
        if (lhs[i] != rhs[i])
            return rhs[i];
    }
    return false;
}

template <std::size_t N>
auto operator<=(std::bitset<N> const& lhs, std::bitset<N> const& rhs) -> bool
{
    return lhs < rhs || lhs == rhs;
}

template <std::size_t N>
auto operator>(std::bitset<N> const& lhs, std::bitset<N> const& rhs) -> bool
{
    return !(lhs <= rhs);
}

template <std::size_t N>
auto operator>=(std::bitset<N> const& lhs, std::bitset<N> const& rhs) -> bool
{
    return lhs > rhs || lhs == rhs;
}

}  // namespace utility::detail::usign
#endif  // UTILITY_DETAIL_USIGN_BIT_COMPARISONS_HPP
