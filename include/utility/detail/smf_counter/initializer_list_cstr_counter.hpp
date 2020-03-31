#ifndef UTILITY_DETAIL_SMF_COUNTER_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
#include <string>
#include <type_traits>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Initializer_list_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the initializer
     *  list constructor. */
    static void increment_initializer_list_cstr_count()
    {
        ++initializer_list_cstr_count_;
    }

    /// Retrieve number of times initializer list constructor has been called.
    static auto get_initializer_list_cstr_count() -> Count_t
    {
        return initializer_list_cstr_count_;
    }

    /// Set count of initializer list constructor to zero.
    static void reset_initializer_list_cstr_count()
    {
        initializer_list_cstr_count_ = 0;
    }

    /// Generate string with count info for the initializer list constructor.
    static auto initializer_list_cstr_count_as_string() -> std::string
    {
        auto description = utility::get_type_info<T>().full_type_name();
        description.append("{std::initializer_list<");
        description.append(
            utility::get_type_info<typename std::remove_extent<T>::type>());
        description.append(">} called ");
        description.append(std::to_string(initializer_list_cstr_count_));
        description.append(" times.");
        return description;
    }

   private:
    static inline auto initializer_list_cstr_count_ = Count_t{0};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
