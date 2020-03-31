#ifndef UTILITY_DETAIL_SMF_COUNTER_MOVE_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_MOVE_CSTR_COUNTER_HPP
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Move_cstr_counter {
   public:
    /// Increment the counter by one.
    /** Should be called by the class inheriting this class in the move
     *  constructor. */
    static void increment_move_cstr_count() { ++move_cstr_count_; }

    /// Retrieve number of times the move constructor has been called.
    static auto get_move_cstr_count() -> Count_t { return move_cstr_count_; }

    /// Set count of move constructor to zero.
    static void reset_move_cstr_count() { move_cstr_count_ = 0; }

    /// Generate string with count info for the move constructor.
    static auto move_cstr_count_as_string() -> std::string
    {
        const auto type_name = get_type_info<T>().full_type_name();
        auto result          = type_name;
        result.append("(");
        result.append(type_name);
        result.append("&&) called ");
        result.append(std::to_string(move_cstr_count_));
        result.append(" times.");
        return result;
    }

   private:
    static inline auto move_cstr_count_ = Count_t{0};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_MOVE_CSTR_COUNTER_HPP
