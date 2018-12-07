#ifndef UTILITY_TO_FILE_HPP
#define UTILITY_TO_FILE_HPP
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

namespace utility {

/// Sends \p container to a file \p filename with \p delimiter between values.
template <typename Container_t>
void to_file(const Container_t& container,
             const std::string& filename,
             const std::string& delimiter = "\n",
             std::ios_base::openmode mode = std::ios_base::out) {
    auto ofs = std::ofstream{filename, mode};
    std::copy(std::begin(container), std::end(container),
              std::ostream_iterator<typename Container_t::value_type>(
                  ofs, delimiter.c_str()));
}

}  // namespace utility
#endif  // UTILITY_TO_FILE_HPP
