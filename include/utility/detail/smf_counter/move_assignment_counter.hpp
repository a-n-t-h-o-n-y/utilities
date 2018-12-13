#ifndef UTILITY_DETAIL_SMF_COUNTER_MOVE_ASSIGNMENT_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_MOVE_ASSIGNMENT_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename>
class Move_assignment_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the move
     *  assignment operator. */
    static void increment_move_assignment_count();

    /// Retrieve number of times the move assignment operator has been called.
    static Count_t get_move_assignment_count();

    /// Set count of move assignment operator to zero.
    static void reset_move_assignment_count();

    /// Generate string with count info for the move assignment operator.
    static std::string move_assignment_count_as_string();

   private:
    static Count_t move_assignment_count_;
};

template <typename T>
Count_t Move_assignment_counter<T>::move_assignment_count_{0};

template <typename T>
void Move_assignment_counter<T>::increment_move_assignment_count() {
    ++move_assignment_count_;
}

template <typename T>
Count_t Move_assignment_counter<T>::get_move_assignment_count() {
    return move_assignment_count_;
}

template <typename T>
void Move_assignment_counter<T>::reset_move_assignment_count() {
    move_assignment_count_ = 0;
}

template <typename T>
std::string Move_assignment_counter<T>::move_assignment_count_as_string() {
    const auto type_name = std::string{get_type_info<T>()};
    auto result = type_name;
    result.append("& operator=(");
    result.append(type_name);
    result.append("&&) called ");
    result.append(std::to_string(move_assignment_count_));
    result.append(" times.");
    return result;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_MOVE_ASSIGNMENT_COUNTER_HPP
