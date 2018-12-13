#ifndef UTILITY_STRONG_GUARANTEE_HPP
#define UTILITY_STRONG_GUARANTEE_HPP
#include <type_traits>
#include <utility>

namespace utility {

/// Gives operations on containers the Strong Exception Guaranteed
/** Performs a copy and swap. Specify the member function type to avoid
 *  ambiguity. */
template <typename Operation_t, typename Container_t, typename... Args>
auto make_operation_strong(Operation_t op, Container_t& c, Args&&... args) {
    auto copy = Container_t{c};
    try {
        return (c.*op)(std::forward<Args>(args)...);
    } catch (...) {  // If operation failed.
        c.swap(copy);
        throw;
    }
}

}  // namespace utility
#endif  // UTILITY_STRONG_GUARANTEE_HPP
