#ifndef UTILITY_DETAIL_COPY_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_COPY_CSTR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename>
class Copy_cstr_counter {
   public:
    /// Increment the counter by one. Should be called by the class inheriting
    /// this class in the copy constructor.
    static void increment_copy_cstr_count();

    /// Retrieve number of times the copy constructor has been called.
    static Count_t get_copy_cstr_count();

    /// Set count of copy constructor to zero.
    static void reset_copy_cstr_count();

    /// Generate string with count info for the copy constructor.
    static std::string copy_cstr_count_as_string();

   private:
    static Count_t copy_cstr_count_;
};

template <typename T>
Count_t Copy_cstr_counter<T>::copy_cstr_count_{0};

template <typename T>
void Copy_cstr_counter<T>::increment_copy_cstr_count() {
    ++copy_cstr_count_;
}

template <typename T>
Count_t Copy_cstr_counter<T>::get_copy_cstr_count() {
    return copy_cstr_count_;
}

template <typename T>
void Copy_cstr_counter<T>::reset_copy_cstr_count() {
    copy_cstr_count_ = 0;
}

template <typename T>
std::string Copy_cstr_counter<T>::copy_cstr_count_as_string() {
    std::string type_name{get_type_info<T>()};
    std::string result{type_name};
    result.append("(");
    result.append("const ");
    result.append(type_name);
    result.append("&) called ");
    result.append(std::to_string(copy_cstr_count_));
    result.append(" times.");
    return result;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_COPY_CSTR_COUNTER_HPP
