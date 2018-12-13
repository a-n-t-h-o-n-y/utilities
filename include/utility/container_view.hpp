#ifndef UTILITY_CONTAINER_VIEW_HPP
#define UTILITY_CONTAINER_VIEW_HPP
#include <ios>
#include <iterator>
#include <sstream>
#include <string>

namespace utility {

/// Return formatted output from [first, last).
template <typename Input_iterator_t>
std::string container_view(Input_iterator_t first, Input_iterator_t last) {
    auto ss = std::stringstream{"{", std::ios_base::app | std::ios_base::out};
    auto seperator = std::string{""};
    while (first != last) {
        ss << seperator << *first;
        seperator = ", ";
        ++first;
    }
    ss << "}";
    return ss.str();
}

/// Return formatted output of container elements.
template <typename Container_t>
std::string container_view(const Container_t& container) {
    return container_view(std::begin(container), std::end(container));
}

}  // namespace utility
#endif  // UTILITY_CONTAINER_VIEW_HPP
