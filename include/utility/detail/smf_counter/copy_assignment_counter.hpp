#ifndef UTILITY_DETAIL_SMF_COUNTER_COPY_ASSIGNMENT_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_COPY_ASSIGNMENT_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename>
class Copy_assignment_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the copy
     *  assignment operator. */
    static void increment_copy_assignment_count();

    /// Retrieve number of times the copy assignment operator has been called.
    static Count_t get_copy_assignment_count();

    /// Set count of copy assignment operator to zero.
    static void reset_copy_assignment_count();

    /// Generate string with count info for the copy assignment operator.
    static std::string copy_assignment_count_as_string();

   private:
    static Count_t copy_assignment_count_;
};

template <typename T>
Count_t Copy_assignment_counter<T>::copy_assignment_count_{0};

template <typename T>
void Copy_assignment_counter<T>::increment_copy_assignment_count() {
    ++copy_assignment_count_;
}

template <typename T>
Count_t Copy_assignment_counter<T>::get_copy_assignment_count() {
    return copy_assignment_count_;
}

template <typename T>
void Copy_assignment_counter<T>::reset_copy_assignment_count() {
    copy_assignment_count_ = 0;
}

template <typename T>
std::string Copy_assignment_counter<T>::copy_assignment_count_as_string() {
    const auto type_name = std::string{get_type_info<T>()};
    auto result = type_name;
    result.append("& operator=(const ");
    result.append(type_name);
    result.append("&) called ");
    result.append(std::to_string(copy_assignment_count_));
    result.append(" times.");
    return result;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_COPY_ASSIGNMENT_COUNTER_HPP
