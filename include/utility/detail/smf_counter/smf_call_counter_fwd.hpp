#ifndef UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_FWD_HPP
#define UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_FWD_HPP
namespace utility {

/// Special Member Function Call Counter
/** Transparently wraps type T and  counts the number of times each special
 *  member function is called. Requires C++17. */
template <typename T, typename SFINAE = void>
class SMF_call_counter;

}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_FWD_HPP
