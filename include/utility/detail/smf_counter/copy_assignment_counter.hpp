#ifndef UTILITY_DETAIL_SMF_COUNTER_COPY_ASSIGNMENT_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_COPY_ASSIGNMENT_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Copy_assignment_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the copy
     *  assignment operator. */
    static void increment_copy_assignment_count() { ++copy_assignment_count_; }

    /// Retrieve number of times the copy assignment operator has been called.
    static auto get_copy_assignment_count() -> Count_t
    {
        return copy_assignment_count_;
    }

    /// Set count of copy assignment operator to zero.
    static void reset_copy_assignment_count() { copy_assignment_count_ = 0; }

    /// Generate string with count info for the copy assignment operator.
    static auto copy_assignment_count_as_string() -> std::string
    {
        auto const type_name = get_type_info<T>().full_type_name();
        auto result          = type_name;
        result.append("& operator=(const ");
        result.append(type_name);
        result.append("&) called ");
        result.append(std::to_string(copy_assignment_count_));
        result.append(" times.");
        return result;
    }

   private:
    static inline auto copy_assignment_count_ = Count_t{0};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_COPY_ASSIGNMENT_COUNTER_HPP
