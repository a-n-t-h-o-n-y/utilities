#ifndef UTILITY_DETAIL_SMF_COUNTER_MOVE_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_MOVE_CSTR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename>
class Move_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the move
     *  constructor. */
    static void increment_move_cstr_count();

    /// Retrieve number of times the move constructor has been called.
    static Count_t get_move_cstr_count();

    /// Set count of move constructor to zero.
    static void reset_move_cstr_count();

    /// Generate string with count info for the move constructor.
    static std::string move_cstr_count_as_string();

   private:
    static Count_t move_cstr_count_;
};

template <typename T>
Count_t Move_cstr_counter<T>::move_cstr_count_{0};

template <typename T>
void Move_cstr_counter<T>::increment_move_cstr_count() {
    ++move_cstr_count_;
}

template <typename T>
Count_t Move_cstr_counter<T>::get_move_cstr_count() {
    return move_cstr_count_;
}

template <typename T>
void Move_cstr_counter<T>::reset_move_cstr_count() {
    move_cstr_count_ = 0;
}

template <typename T>
std::string Move_cstr_counter<T>::move_cstr_count_as_string() {
    const auto type_name = std::string{get_type_info<T>()};
    auto result = type_name;
    result.append("(");
    result.append(type_name);
    result.append("&&) called ");
    result.append(std::to_string(move_cstr_count_));
    result.append(" times.");
    return result;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_MOVE_CSTR_COUNTER_HPP
