#ifndef UTILITY_DETAIL_MEMORY_VIEW_TO_UPPER_CASE_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_TO_UPPER_CASE_HPP
#include <cctype>
#include <string>

namespace utility::detail::memory_view {

void to_upper_case(std::string& s)
{
    for (char& c : s)
        c = std::toupper(static_cast<unsigned char>(c));
}

auto to_upper_case_copy(std::string s) -> std::string
{
    to_upper_case(s);
    return s;
}

}  // namespace utility::detail::memory_view
#endif  // UTILITY_DETAIL_MEMORY_VIEW_TO_UPPER_CASE_HPP
