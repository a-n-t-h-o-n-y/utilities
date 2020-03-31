#ifndef UTILITY_NARROW_CAST_HPP
#define UTILITY_NARROW_CAST_HPP
#include <stdexcept>
#include <string>

#include <utility/type_info.hpp>

namespace utility {
namespace detail::narrow_cast {

template <typename Target_t, typename Source_t>
auto create_message() -> std::string
{
    return "narrow_cast<" + std::string{get_type_info<Target_t>()} + ">(" +
           std::string{get_type_info<Source_t>()} + ") failed";
}

}  // namespace detail::narrow_cast

/// Throws std::runtime_error if value being cast is too large for Target_t.
template <typename Target_t, typename Source_t>
auto narrow_cast(Source_t const& source) noexcept(false) -> Target_t
{
    auto const result = static_cast<Target_t>(source);
    if (static_cast<Source_t>(result) != source) {
        throw std::runtime_error{
            detail::narrow_cast::create_message<Target_t, Source_t>()};
    }
    return result;
}

}  // namespace utility
#endif  // UTILITY_NARROW_CAST_HPP
