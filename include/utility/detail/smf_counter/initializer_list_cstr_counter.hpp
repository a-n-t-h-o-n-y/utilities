#ifndef UTILITY_DETAIL_SMF_COUNTER_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
#include <string>
#include <type_traits>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename T>
class Initializer_list_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the initializer
     *  list constructor. */
    static void increment_initializer_list_cstr_count();

    /// Retrieve number of times initializer list constructor has been called.
    static Count_t get_initializer_list_cstr_count();

    /// Set count of initializer list constructor to zero.
    static void reset_initializer_list_cstr_count();

    /// Generate string with count info for the initializer list constructor.
    static std::string initializer_list_cstr_count_as_string();

   private:
    static Count_t initializer_list_cstr_count_;
};

// IMPLEMENTATION - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
Count_t Initializer_list_cstr_counter<T>::initializer_list_cstr_count_{0};

template <typename T>
void Initializer_list_cstr_counter<T>::increment_initializer_list_cstr_count() {
    ++initializer_list_cstr_count_;
}

template <typename T>
Count_t Initializer_list_cstr_counter<T>::get_initializer_list_cstr_count() {
    return initializer_list_cstr_count_;
}

template <typename T>
void Initializer_list_cstr_counter<T>::reset_initializer_list_cstr_count() {
    initializer_list_cstr_count_ = 0;
}

template <typename T>
std::string
Initializer_list_cstr_counter<T>::initializer_list_cstr_count_as_string() {
    auto description = std::string{utility::get_type_info<T>()};
    description.append("{std::initializer_list<");
    description.append(
        utility::get_type_info<typename std::remove_extent<T>::type>());
    description.append(">} called ");
    description.append(std::to_string(initializer_list_cstr_count_));
    description.append(" times.");
    return description;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
