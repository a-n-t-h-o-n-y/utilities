#ifndef UTILITY_DETAIL_SMF_COUNTER_DEFAULT_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_DEFAULT_CSTR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename>
class Default_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the default
     *  constructor. */
    static void increment_default_cstr_count();

    /// Retrieve number of times the default constructor has been called.
    static Count_t get_default_cstr_count();

    /// Set count of default constructor to zero.
    static void reset_default_cstr_count();

    /// Generate string with count info for the default constructor.
    static std::string default_cstr_count_as_string();

   private:
    static Count_t default_cstr_count_;
};

template <typename T>
Count_t Default_cstr_counter<T>::default_cstr_count_{0};

template <typename T>
void Default_cstr_counter<T>::increment_default_cstr_count() {
    ++default_cstr_count_;
}

template <typename T>
Count_t Default_cstr_counter<T>::get_default_cstr_count() {
    return default_cstr_count_;
}

template <typename T>
void Default_cstr_counter<T>::reset_default_cstr_count() {
    default_cstr_count_ = 0;
}

template <typename T>
std::string Default_cstr_counter<T>::default_cstr_count_as_string() {
    auto result = std::string{get_type_info<T>()};
    result.append("() called ");
    result.append(std::to_string(default_cstr_count_));
    result.append(" times.");
    return result;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_DEFAULT_CSTR_COUNTER_HPP
