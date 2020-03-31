#ifndef UTILITY_DETAIL_SMF_COUNTER_DESTRUCTOR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_DESTRUCTOR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Destructor_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the destructor.*/
    static void increment_destructor_count() { ++destructor_count_; }

    /// Retrieve number of times the destructor has been called.
    static auto get_destructor_count() -> Count_t { return destructor_count_; }

    /// Set count of destructor to zero.
    static void reset_destructor_count() { destructor_count_ = 0; }

    /// Generate string with count info for the destructor.
    static auto destructor_count_as_string() -> std::string
    {
        auto result = std::string{"~"};
        result.append(get_type_info<T>().full_type_name());
        result.append("() called ");
        result.append(std::to_string(destructor_count_));
        result.append(" times.");
        return result;
    }

   private:
    static inline auto destructor_count_ = Count_t{0};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_DESTRUCTOR_COUNTER_HPP
