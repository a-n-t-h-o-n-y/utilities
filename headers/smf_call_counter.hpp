#ifndef UTILITY_SMF_CALL_COUNTER_HPP
#define UTILITY_SMF_CALL_COUNTER_HPP
#include <cstdint>
#include <map>
#include <utility>
#include <vector>

#include "type_info.hpp"

namespace utility {

/// Type to hold number of calls made for each SMF.
using Count_t = std::uint64_t;

/// Special Member Function Call Counter
///
/// Transparently wraps type T and  counts the number of times each special
/// member function is called. Miscellaneous constructors are counted, and their
/// counts accessible by the types passed into the constructor's parameter list.
template <typename T>
class SMF_call_counter : public T {
   public:
    SMF_call_counter();

    template <typename... Args>
    SMF_call_counter(Args&&... args);

    SMF_call_counter(const SMF_call_counter& other);
    SMF_call_counter(SMF_call_counter& other);
    SMF_call_counter(SMF_call_counter&& other);

    SMF_call_counter& operator=(const SMF_call_counter& other);
    SMF_call_counter& operator=(SMF_call_counter&& other);

    ~SMF_call_counter();

    /// Retrieve counts of miscellaneous constructors by providing types passed
    /// to the constructor's parameter list. Constructor counts are held by the
    /// types passed to the constructor and are not necessarily the exact types
    /// in the constructor signature.
    template <typename... Args>
    static Count_t get_cstr_count();

    /// Retrieves the total count of all the miscellaneous constructors.
    static Count_t get_misc_cstr_count();

    /// Retrieve number of times the default constructor has been called.
    static Count_t get_default_cstr_count();

    /// Retrieve number of times the copy constructor has been called.
    static Count_t get_copy_cstr_count();

    /// Retrieve number of times the move constructor has been called.
    static Count_t get_move_cstr_count();

    /// Retrieve number of times the copy assignment operator has been called.
    static Count_t get_copy_assignment_count();

    /// Retrieve number of times the move assignment operator has been called.
    static Count_t get_move_assignment_count();

    /// Retrieve number of times the destructor has been called.
    static Count_t get_destructor_count();

    /// Set count of miscellaneous constructors to zero. Constructor identified
    /// by types passed to the constructor's parameter list.
    template <typename... Args>
    static void reset_cstr_count();

    /// Set count of all miscellaneous constructors to zero.
    static void reset_misc_cstr_count();

    /// Set all counts to zero.
    static void reset_counts();

    /// Set count of default constructor to zero.
    static void reset_default_cstr_count();

    /// Set count of copy constructor to zero.
    static void reset_copy_cstr_count();

    /// Set count of move constructor to zero.
    static void reset_move_cstr_count();

    /// Set count of copy assignment operator to zero.
    static void reset_copy_assignment_count();

    /// Set count of move assignment operator to zero.
    static void reset_move_assignment_count();

    /// Set count of destructor to zero.
    static void reset_destructor_count();

    /// Generate string with count info for all Special Member Functions.
    static std::string all_counts_as_string();

    /// Generate string with count info for miscellaneous constructors,
    /// determined by the types passed to the constructor's parameter list.
    template <typename... Args>
    static std::string cstr_count_as_string();

    /// Generate string with count info for all miscellaneous constructors.
    static std::string misc_cstr_counts_as_string();

    /// Generate string with count info for the default constructor.
    static std::string default_cstr_count_as_string();

    /// Generate string with count info for the copy constructor.
    static std::string copy_cstr_count_as_string();

    /// Generate string with count info for the move constructor.
    static std::string move_cstr_count_as_string();

    /// Generate string with count info for the copy assignment operator.
    static std::string copy_assignment_count_as_string();

    /// Generate string with count info for the move assignment operator.
    static std::string move_assignment_count_as_string();

    /// Generate string with count info for the destructor.
    static std::string destructor_count_as_string();

   private:
    static Count_t default_cstr_count_;
    static Count_t copy_cstr_count_;
    static Count_t move_cstr_count_;
    static Count_t copy_assignment_count_;
    static Count_t move_assignment_count_;
    static Count_t destructor_count_;

    using Parameter_list = std::vector<Type_info>;
    static std::map<Parameter_list, Count_t> misc_counts_;
};

// STATIC VARIABLE INITIALIZATION - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
Count_t SMF_call_counter<T>::default_cstr_count_{0};
template <typename T>
std::map<typename SMF_call_counter<T>::Parameter_list, Count_t>
    SMF_call_counter<T>::misc_counts_;
template <typename T>
Count_t SMF_call_counter<T>::copy_cstr_count_{0};
template <typename T>
Count_t SMF_call_counter<T>::move_cstr_count_{0};
template <typename T>
Count_t SMF_call_counter<T>::copy_assignment_count_{0};
template <typename T>
Count_t SMF_call_counter<T>::move_assignment_count_{0};
template <typename T>
Count_t SMF_call_counter<T>::destructor_count_{0};

// SMF IMPLEMENTATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
SMF_call_counter<T>::SMF_call_counter() {
    ++default_cstr_count_;
}

template <typename T>
template <typename... Args>
SMF_call_counter<T>::SMF_call_counter(Args&&... args)
    : T{std::forward<Args>(args)...} {
    Parameter_list params{get_type_info<Args>()...};
    if (misc_counts_.count(params) == 1) {
        ++misc_counts_.at(params);
    } else {
        misc_counts_[params] = 1;
    }
}

template <typename T>
SMF_call_counter<T>::SMF_call_counter(const SMF_call_counter& other)
    : T{other} {
    ++copy_cstr_count_;
}

// Supresses the variadic template from handling non-const copies.
template <typename T>
SMF_call_counter<T>::SMF_call_counter(SMF_call_counter& other)
    : SMF_call_counter{const_cast<const SMF_call_counter&>(other)} {}

template <typename T>
SMF_call_counter<T>::SMF_call_counter(SMF_call_counter&& other)
    : T{std::move(other)} {
    ++move_cstr_count_;
}

// Let base class decide self-assignment, it is counted as a call here.
template <typename T>
SMF_call_counter<T>& SMF_call_counter<T>::operator=(
    const SMF_call_counter& other) {
    T::operator=(other);
    ++copy_assignment_count_;
    return *this;
}

// Let base class decide self-assignment, it is counted as a call here.
template <typename T>
SMF_call_counter<T>& SMF_call_counter<T>::operator=(SMF_call_counter&& other) {
    T::operator=(std::move(other));
    ++move_assignment_count_;
    return *this;
}

template <typename T>
SMF_call_counter<T>::~SMF_call_counter() {
    ++destructor_count_;
}

// GET IMPLEMENTATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
Count_t SMF_call_counter<T>::get_default_cstr_count() {
    return default_cstr_count_;
}

template <typename T>
template <typename... Args>
Count_t SMF_call_counter<T>::get_cstr_count() {
    Parameter_list params{get_type_info<Args>()...};
    if (misc_counts_.count(params) == 1) {
        return misc_counts_.at(params);
    }
    return 0;
}

template <typename T>
Count_t SMF_call_counter<T>::get_misc_cstr_count() {
    Count_t total{0};
    for (const auto& param_count_pair : misc_counts_) {
        total += param_count_pair.second;
    }
    return total;
}

template <typename T>
Count_t SMF_call_counter<T>::get_copy_cstr_count() {
    return copy_cstr_count_;
}

template <typename T>
Count_t SMF_call_counter<T>::get_move_cstr_count() {
    return move_cstr_count_;
}

template <typename T>
Count_t SMF_call_counter<T>::get_copy_assignment_count() {
    return copy_assignment_count_;
}

template <typename T>
Count_t SMF_call_counter<T>::get_move_assignment_count() {
    return move_assignment_count_;
}

template <typename T>
Count_t SMF_call_counter<T>::get_destructor_count() {
    return destructor_count_;
}

template <typename T>
void SMF_call_counter<T>::reset_counts() {
    reset_default_cstr_count();
    reset_misc_cstr_count();
    reset_copy_cstr_count();
    reset_move_cstr_count();
    reset_copy_assignment_count();
    reset_move_assignment_count();
    reset_destructor_count();
}

template <typename T>
void SMF_call_counter<T>::reset_default_cstr_count() {
    default_cstr_count_ = 0;
}

template <typename T>
template <typename... Args>
void SMF_call_counter<T>::reset_cstr_count() {
    Parameter_list params{get_type_info<Args>()...};
    if (misc_counts_.count(params) == 1) {
        misc_counts_.erase(misc_counts_.find(params));
    }
}

template <typename T>
void SMF_call_counter<T>::reset_misc_cstr_count() {
    misc_counts_.clear();
}

template <typename T>
void SMF_call_counter<T>::reset_copy_cstr_count() {
    copy_cstr_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_move_cstr_count() {
    move_cstr_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_copy_assignment_count() {
    copy_assignment_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_move_assignment_count() {
    move_assignment_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_destructor_count() {
    destructor_count_ = 0;
}

template <typename T>
std::string SMF_call_counter<T>::all_counts_as_string() {
    return default_cstr_count_as_string() + "\n" +
           misc_cstr_counts_as_string() + "\n" + copy_cstr_count_as_string() +
           "\n" + move_cstr_count_as_string() + "\n" +
           copy_assignment_count_as_string() + "\n" +
           move_assignment_count_as_string() + "\n" +
           destructor_count_as_string();
}

template <typename T>
template <typename... Args>
std::string SMF_call_counter<T>::cstr_count_as_string() {
    Parameter_list params{get_type_info<Args>()...};
    std::string result{get_type_info<T>()};
    result.append("(");
    std::string seperator;
    for (const Type_info& info : params) {
        result.append(seperator);
        result.append(static_cast<std::string>(info));
        seperator = ", ";
    }
    result.append(")");
    result.append(" called ");
    if (misc_counts_.count(params) == 1) {
        result.append(std::to_string(misc_counts_.at(params)));
    } else {
        result.append("0");
    }
    result.append(" times.");
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::misc_cstr_counts_as_string() {
    std::string result;
    for (const auto& param_count_pair : misc_counts_) {
        result.append(get_type_info<T>());
        result.append("(");
        std::string seperator;
        for (const Type_info& info : param_count_pair.first) {
            result.append(seperator);
            result.append(static_cast<std::string>(info));
            seperator = ", ";
        }
        result.append(")");
        result.append(" called ");
        result.append(std::to_string(param_count_pair.second));
        result.append(" times.\n");
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::default_cstr_count_as_string() {
    std::string result{get_type_info<T>()};
    result.append("() called ");
    result.append(std::to_string(default_cstr_count_));
    result.append(" times.");
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::copy_cstr_count_as_string() {
    std::string type_name{get_type_info<T>()};
    std::string result{type_name};
    result.append("(");
    result.append("const ");
    result.append(type_name);
    result.append("&) called ");
    result.append(std::to_string(copy_cstr_count_));
    result.append(" times.");
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::move_cstr_count_as_string() {
    std::string type_name{get_type_info<T>()};
    std::string result{type_name};
    result.append("(");
    result.append(type_name);
    result.append("&&) called ");
    result.append(std::to_string(copy_cstr_count_));
    result.append(" times.");
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::copy_assignment_count_as_string() {
    std::string type_name{get_type_info<T>()};
    std::string result{type_name};
    result.append("& operator=(const ");
    result.append(type_name);
    result.append("&) called ");
    result.append(std::to_string(copy_assignment_count_));
    result.append(" times.");
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::move_assignment_count_as_string() {
    std::string type_name{get_type_info<T>()};
    std::string result{type_name};
    result.append("& operator=(");
    result.append(type_name);
    result.append("&&) called ");
    result.append(std::to_string(move_assignment_count_));
    result.append(" times.");
    return result;
}

template <typename T>
std::string SMF_call_counter<T>::destructor_count_as_string() {
    std::string result{"~"};
    result.append(get_type_info<T>());
    result.append("() called ");
    result.append(std::to_string(destructor_count_));
    result.append(" times.");
    return result;
}

}  // namespace utility
#endif  // UTILITY_SMF_CALL_COUNTER_HPP
