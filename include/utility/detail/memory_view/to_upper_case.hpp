#ifndef UTILITY_DETAIL_MEMORY_VIEW_TO_UPPER_CASE_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_TO_UPPER_CASE_HPP
#include <cctype>
#include <string>

namespace utility {
namespace detail {
namespace memory_view {

void to_upper_case(std::string& s) {
    for (char& c : s) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
}

std::string to_upper_case_copy(std::string s) {
    to_upper_case(s);
    return s;
}

}  // namespace memory_view
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_MEMORY_VIEW_TO_UPPER_CASE_HPP
