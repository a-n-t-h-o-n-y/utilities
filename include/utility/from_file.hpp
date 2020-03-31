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
   private:
    using Base_t = std::ctype<Char_t>;

   public:
    Delimiters(std::string const& delimiters)
        : Base_t(make_table(delimiters, table_))
    {}

   private:
    typename Base_t::mask table_[Base_t::table_size];

   private:
    static auto make_table(std::string const& delimiters,
                           typename Base_t::mask* table) ->
        typename Base_t::mask const*
    {
        auto mask = Base_t::classic_table();
        std::copy(mask, mask + Base_t::table_size, table);
        table[static_cast<unsigned>(' ')]  = 0;
        table[static_cast<unsigned>('\f')] = 0;
        table[static_cast<unsigned>('\n')] = 0;
        table[static_cast<unsigned>('\r')] = 0;
        table[static_cast<unsigned>('\t')] = 0;
        table[static_cast<unsigned>('\v')] = 0;
        for (unsigned char c : delimiters)
            table[static_cast<unsigned>(c)] |= Base_t::space;
        return table;
    }
};

}  // namespace detail

/// Retrieves values from a delimited file, into a given Container_t object.
template <typename Container_t = std::vector<int>>
auto from_file(const std::string& filename,
               const std::string& delimiters = " \n\f\r\t\v") -> Container_t
{
    using Filestream_t = std::ifstream;
    using Value_t      = typename Container_t::value_type;

    auto ifs = Filestream_t{filename};
    ifs.imbue(std::locale{
        ifs.getloc(),
        new detail::Delimiters<typename Filestream_t::char_type>{delimiters}});
    // Delimiters ^^ object is not leaked.

    auto container = Container_t{};
    std::copy(std::istream_iterator<Value_t>(ifs),
              std::istream_iterator<Value_t>(), std::back_inserter(container));
    return container;
}

}  // namespace utility
#endif  // UTILITY_FROM_FILE_HPP
