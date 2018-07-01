#ifndef UTILITY_NARROW_CAST_HPP
#define UTILITY_NARROW_CAST_HPP
#include <stdexcept>
#include <string>

namespace utility {

/// Throws runtime_error if value being cast is too large for Source type.
template <typename Target, typename Source>
Target narrow_cast(const Source& source) noexcept(false) {
    auto result = static_cast<Target>(source);
    if (static_cast<Source>(result) != source) {
        std::string message{std::string{"narrow_cast<"} +
                            typeid(Target).name() + ">(" +
                            typeid(Source).name() + ") failed"};
        throw std::runtime_error{message};
    }
    return result;
}

}  // namespace utility
#endif  // UTILITY_NARROW_CAST_HPP
