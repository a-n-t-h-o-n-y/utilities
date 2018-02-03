#ifndef UTILITY_STRONG_GUARANTEE_HPP
#define UTILITY_STRONG_GUARANTEE_HPP
#include <type_traits>
#include <utility>

namespace utility {

/// Gives operations on containers the Strong Exception Guaranteed by a copy and
/// swap. Specify the member function type to avoid ambiguity.
template <typename Operation, typename Container, typename... Args>
auto make_operation_strong(Operation op, Container& c, Args&&... args) ->
    typename std::result_of<decltype(op)(Container*, Args...)>::type {
    Container temp{c};
    // Operations need to take place on the original container, not a copy,
    // specifically for iterator parameters.
    try {
        typename std::result_of<decltype(op)(Container*, Args...)>::type
            result = (c.*op)(std::forward<Args>(args)...);
        return result;
    } catch (...) {  // If operation failed, then swap in the copy you took.
        c.swap(temp);
        throw;
    }
}

}  // namespace utility
#endif  // UTILITY_STRONG_GUARANTEE_HPP
