#ifndef UTILITY_DETAIL_SMF_COUNTER_DESTRUCTOR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_DESTRUCTOR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename>
class Destructor_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the destructor.
     * */
    static void increment_destructor_count();

    /// Retrieve number of times the destructor has been called.
    static Count_t get_destructor_count();

    /// Set count of destructor to zero.
    static void reset_destructor_count();

    /// Generate string with count info for the destructor.
    static std::string destructor_count_as_string();

   private:
    static Count_t destructor_count_;
};

template <typename T>
Count_t Destructor_counter<T>::destructor_count_{0};

template <typename T>
void Destructor_counter<T>::increment_destructor_count() {
    ++destructor_count_;
}

template <typename T>
Count_t Destructor_counter<T>::get_destructor_count() {
    return destructor_count_;
}

template <typename T>
void Destructor_counter<T>::reset_destructor_count() {
    destructor_count_ = 0;
}

template <typename T>
std::string Destructor_counter<T>::destructor_count_as_string() {
    auto result = std::string{"~"};
    result.append(get_type_info<T>());
    result.append("() called ");
    result.append(std::to_string(destructor_count_));
    result.append(" times.");
    return result;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_DESTRUCTOR_COUNTER_HPP
