#ifndef UTILITY_CONTAINER_VIEW_HPP
#define UTILITY_CONTAINER_VIEW_HPP
#include <sstream>
#include <string>

namespace utility {

/// Return formatted output of container elements.
template <typename InputIterator>
std::string container_view(InputIterator first, InputIterator last) {
    std::stringstream ss{"{ ", std::ios_base::app | std::ios_base::out};
    std::string seperator;
    while (first != last) {
        ss << seperator << *first;
        seperator = ", ";
        ++first;
    }
    ss << " }";
    return ss.str();
}

/// Return formatted output of container elements.
template <typename Container>
std::string container_view(const Container& container) {
    return container_view(std::begin(container), std::end(container));
}

}  // namespace utility
#endif  // UTILITY_CONTAINER_VIEW_HPP
