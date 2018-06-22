#ifndef UTILITY_SMF_CALL_COUNTER_HPP
#define UTILITY_SMF_CALL_COUNTER_HPP
#include <cstdint>
#include <utility>

#include "type_info.hpp"

namespace utility {

/// Type to hold number of calls made for each SMF.
using Count_t = std::uint64_t;

/// Special Member Function Call Counter
///
/// Transparently wraps type T and  counts the number of times each special
/// member function is called.
template <typename T>
class SMF_call_counter : public T {
   public:
    // can have a dynamic list with type id tuples or something. Maybe not that
    // helpful, but better than nothing?
    // you can hold a map with type_index list as key, count as value. getting
    // the const/volitile-ness in the type is important.

    // access template function: get_count<int, const std::string&>(); will look
    // up those type id's index, in the correct order too, and return the value
    // in the map.
    SMF_call_counter();

    template <typename... Args>
    SMF_call_counter(Args&&... args);

    SMF_call_counter(const SMF_call_counter& other);
    SMF_call_counter(SMF_call_counter& other);
    SMF_call_counter(SMF_call_counter&& other);

    SMF_call_counter& operator=(const SMF_call_counter& other);
    SMF_call_counter& operator=(SMF_call_counter&& other);

    ~SMF_call_counter();

    /// Retrieve counts.
    static Count_t get_default_cstr_count();
    static Count_t get_misc_cstr_count();
    static Count_t get_copy_cstr_count();
    static Count_t get_move_cstr_count();
    static Count_t get_copy_assignment_count();
    static Count_t get_move_assignment_count();
    static Count_t get_destructor_count();

    /// Set counts to zero.
    static void reset_counts();
    static void reset_default_cstr_count();
    static void reset_misc_cstr_count();
    static void reset_copy_cstr_count();
    static void reset_move_cstr_count();
    static void reset_copy_assignment_count();
    static void reset_move_assignment_count();
    static void reset_destructor_count();

   private:
    static Count_t default_cstr_count_;
    static Count_t misc_cstr_count_;
    static Count_t copy_cstr_count_;
    static Count_t move_cstr_count_;
    static Count_t copy_assignment_count_;
    static Count_t move_assignment_count_;
    static Count_t destructor_count_;
};

// STATIC VARIABLE INITIALIZATION - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
Count_t SMF_call_counter<T>::default_cstr_count_{0};
template <typename T>
Count_t SMF_call_counter<T>::misc_cstr_count_{0};
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
    ++misc_cstr_count_;
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
Count_t SMF_call_counter<T>::get_misc_cstr_count() {
    return misc_cstr_count_;
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
void SMF_call_counter<T>::reset_misc_cstr_count() {
    misc_cstr_count_ = 0;
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

}  // namespace utility
#endif  // UTILITY_SMF_CALL_COUNTER_HPP
