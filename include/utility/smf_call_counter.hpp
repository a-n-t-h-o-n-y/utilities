#ifndef UTILITY_SMF_CALL_COUNTER_HPP
#define UTILITY_SMF_CALL_COUNTER_HPP

namespace utility {

/// Special Member Function Call Counter
///
/// Transparently wraps type T and  counts the number of times each special
/// member function is called. Requires C++17.
template <typename T, typename SFINAE = void>
class SMF_call_counter;

}  // namespace utility

#include <utility/detail/smf_counter/smf_call_counter_aggregate.hpp>
#include <utility/detail/smf_counter/smf_call_counter_array.hpp>
#include <utility/detail/smf_counter/smf_call_counter_builtin.hpp>
#include <utility/detail/smf_counter/smf_call_counter_class.hpp>

#endif  // UTILITY_SMF_CALL_COUNTER_HPP
