#ifndef UTILITY_THOUSANDS_SEPERATOR_HPP
#define UTILITY_THOUSANDS_SEPERATOR_HPP
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

namespace utility {
template <typename T>
std::string thousands_seperator(T value) {
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

}  // namespace utility
#endif  // UTILITY_THOUSANDS_SEPERATOR_HPP
