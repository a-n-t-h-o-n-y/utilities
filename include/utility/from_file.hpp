#ifndef UTILITY_FROM_FILE_HPP
#define UTILITY_FROM_FILE_HPP
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <cctype>
#include <locale>

namespace utility {
namespace detail {

/// Facet for istream to break on characters other than whitespace.
template <typename Char_t = char>
class Delimiters : public std::ctype<Char_t> {
    using Base_t = std::ctype<Char_t>;

   public:
    Delimiters(const std::string& delimiters)
        : Base_t(make_table(delimiters, table_)) {}

   private:
    static const typename Base_t::mask* make_table(
        const std::string& delimiters,
        typename Base_t::mask* table) {
        auto mask = Base_t::classic_table();
        std::copy(mask, mask + Base_t::table_size, table);
        for (unsigned char c : delimiters) {
            table[static_cast<unsigned>(c)] |= Base_t::space;
        }
        return table;
    }
    typename Base_t::mask table_[Base_t::table_size];
};

}  // namespace detail

/// Retrieves values from a delimited file.
template <typename Container_t = std::vector<int>>
auto from_file(const std::string& filename,
               const std::string& delimiters = " \n\f\r\t\v") {
    using Filestream_t = std::ifstream;
    using Value_t = typename Container_t::value_type;

    Filestream_t ifs{filename};
    ifs.imbue(std::locale{
        ifs.getloc(),
        new detail::Delimiters<typename Filestream_t::char_type>{delimiters}});
    // Delimiters ^^ is not leaked.

    auto container = Container_t{};
    std::copy(std::istream_iterator<Value_t>(ifs),
              std::istream_iterator<Value_t>(), std::back_inserter(container));
    return container;
}

}  // namespace utility
#endif  // UTILITY_FROM_FILE_HPP
