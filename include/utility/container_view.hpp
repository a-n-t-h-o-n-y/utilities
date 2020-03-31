#ifndef UTILITY_CONTAINER_VIEW_HPP
#define UTILITY_CONTAINER_VIEW_HPP
#include <ios>
#include <iterator>
#include <sstream>
#include <string>

namespace utility {

/// Return formatted output from [first, last).
template <typename Input_iterator_t>
auto container_view(Input_iterator_t first, Input_iterator_t last)
    -> std::string
{
    auto ss        = std::ostringstream{"{"};
    auto separator = std::string{""};
    while (first != last) {
        ss << separator << *first;
        separator = ", ";
        ++first;
    }
    ss << "}";
    return ss.str();
}

/// Return formatted output of container elements.
template <typename Container_t>
auto container_view(const Container_t& container) -> std::string
{
    return container_view(std::begin(container), std::end(container));
}

}  // namespace utility
#endif  // UTILITY_CONTAINER_VIEW_HPP
