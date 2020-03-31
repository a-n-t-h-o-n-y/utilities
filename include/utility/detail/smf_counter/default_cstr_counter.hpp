#ifndef UTILITY_DETAIL_SMF_COUNTER_DEFAULT_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_DEFAULT_CSTR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Default_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the default
     *  constructor. */
    static void increment_default_cstr_count() { ++default_cstr_count_; }

    /// Retrieve number of times the default constructor has been called.
    static auto get_default_cstr_count() -> Count_t
    {
        return default_cstr_count_;
    }

    /// Set count of default constructor to zero.
    static void reset_default_cstr_count() { default_cstr_count_ = 0; }

    /// Generate string with count info for the default constructor.
    static auto default_cstr_count_as_string() -> std::string
    {
        auto result = get_type_info<T>().full_type_name();
        result.append("() called ");
        result.append(std::to_string(default_cstr_count_));
        result.append(" times.");
        return result;
    }

   private:
    static inline auto default_cstr_count_ = Count_t{0};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_DEFAULT_CSTR_COUNTER_HPP
