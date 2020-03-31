#ifndef UTILITY_DETAIL_SMF_COUNTER_COPY_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_COPY_CSTR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Copy_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the copy
     *  constructor. */
    static void increment_copy_cstr_count() { ++copy_cstr_count_; }

    /// Retrieve number of times the copy constructor has been called.
    static auto get_copy_cstr_count() -> Count_t { return copy_cstr_count_; }

    /// Set count of copy constructor to zero.
    static void reset_copy_cstr_count() { copy_cstr_count_ = 0; }

    /// Generate string with count info for the copy constructor.
    static auto copy_cstr_count_as_string() -> std::string
    {
        auto const type_name = get_type_info<T>().full_type_name();
        auto result          = type_name;
        result.append("(");
        result.append("const ");
        result.append(type_name);
        result.append("&) called ");
        result.append(std::to_string(copy_cstr_count_));
        result.append(" times.");
        return result;
    }

   private:
    static inline auto copy_cstr_count_ = Count_t{0};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_COPY_CSTR_COUNTER_HPP
