#ifndef UTILITY_SMF_CALL_COUNTER_CLASS_HPP
#define UTILITY_SMF_CALL_COUNTER_CLASS_HPP
#include <string>
#include <utility>

#include "detail/assignment_counter.hpp"
#include "detail/constructor_counter.hpp"
#include "detail/copy_assignment_counter.hpp"
#include "detail/copy_cstr_counter.hpp"
#include "detail/default_cstr_counter.hpp"
#include "detail/destructor_counter.hpp"
#include "detail/move_assignment_counter.hpp"
#include "detail/move_cstr_counter.hpp"

namespace utility {

/// Special Member Function Call Counter
///
/// Transparently wraps type T and  counts the number of times each special
/// member function is called. Miscellaneous constructors are counted, and their
/// counts accessible by the types passed into the constructor's parameter list.
/// Requires C++17 atm.
template <typename T, typename SFINAE = void>
class SMF_call_counter : public T,
                         public detail::Default_cstr_counter<T>,
                         public detail::Constructor_counter<T>,
                         public detail::Copy_cstr_counter<T>,
                         public detail::Move_cstr_counter<T>,
                         public detail::Copy_assignment_counter<T>,
                         public detail::Move_assignment_counter<T>,
                         public detail::Assignment_counter<T>,
                         public detail::Destructor_counter<T>

{
   public:
    /// Increment the Default Constructor counter and default construct T.
    SMF_call_counter();

    /// Increment the Constructor counter for Args and construct T with args...
    template <typename... Args>
    SMF_call_counter(Args&&... args);

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(const SMF_call_counter& other);

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(SMF_call_counter& other);

    /// Increment the Move Constructor counter and move construct T from other.
    SMF_call_counter(SMF_call_counter&& other);

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(const SMF_call_counter& other);

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(SMF_call_counter& other);

    /// Increment the Move Assignment counter and call T::operator=(T&&).
    SMF_call_counter& operator=(SMF_call_counter&& other);

    /// Increment the miscellaneous assignment operator count.
    template <typename U>
    auto operator=(U&& other);

    /// Increment the Destructor counter and call ~T().
    ~SMF_call_counter();

    /// Set all counts to zero.
    static void reset_counts();

    /// Generate string with count info for all Special Member Functions.
    static std::string all_counts_as_string();
};

// IMPLEMENTATION - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DEFAULT CONSTRUCTOR
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>::SMF_call_counter() {
    detail::Default_cstr_counter<T>::increment_default_cstr_count();
}

// MISCELLANEOUS CONSTRUCTOR
template <typename T, typename SFINAE>
template <typename... Args>
SMF_call_counter<T, SFINAE>::SMF_call_counter(Args&&... args)
    : T{std::forward<Args>(args)...} {
    detail::Constructor_counter<T>::template increment_constructor_count<
        Args...>();
}

// COPY CONSTRUCTOR
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>::SMF_call_counter(const SMF_call_counter& other)
    : T{other} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
// Supresses the variadic template from handling non-const copies.
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>::SMF_call_counter(SMF_call_counter& other)
    : SMF_call_counter{const_cast<const SMF_call_counter&>(other)} {}

// MOVE CONSTRUCTOR
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>::SMF_call_counter(SMF_call_counter&& other)
    : T{std::move(other)} {
    detail::Move_cstr_counter<T>::increment_move_cstr_count();
}

// COPY ASSIGNMENT OPERATOR
// Self-Assignment is counted as a call.
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>& SMF_call_counter<T, SFINAE>::operator=(
    const SMF_call_counter& other) {
    T::operator=(other);
    detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
    return *this;
}

// Supresses template from handling non-const assignments.
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>& SMF_call_counter<T, SFINAE>::operator=(
    SMF_call_counter& other) {
    return this->operator=(const_cast<const SMF_call_counter&>(other));
}

// MOVE ASSIGNMENT OPERATOR
// Self-Assignment is counted as a call.
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>& SMF_call_counter<T, SFINAE>::operator=(
    SMF_call_counter&& other) {
    T::operator=(std::move(other));
    detail::Move_assignment_counter<T>::increment_move_assignment_count();
    return *this;
}

// ASSIGNMENT OPERATOR
template <typename T, typename SFINAE>
template <typename U>
auto SMF_call_counter<T, SFINAE>::operator=(U&& other) {
    detail::Assignment_counter<T>::template increment_assignment_count<U>();
    return T::operator=(std::forward<U>(other));
}

// DESTRUCTOR
template <typename T, typename SFINAE>
SMF_call_counter<T, SFINAE>::~SMF_call_counter() {
    detail::Destructor_counter<T>::increment_destructor_count();
}

// RESET_COUNTS()
template <typename T, typename SFINAE>
void SMF_call_counter<T, SFINAE>::reset_counts() {
    detail::Default_cstr_counter<T>::reset_default_cstr_count();
    detail::Constructor_counter<T>::reset_constructor_counts();
    detail::Copy_cstr_counter<T>::reset_copy_cstr_count();
    detail::Move_cstr_counter<T>::reset_move_cstr_count();
    detail::Copy_assignment_counter<T>::reset_copy_assignment_count();
    detail::Move_assignment_counter<T>::reset_move_assignment_count();
    detail::Destructor_counter<T>::reset_destructor_count();
}

// ALL_COUNTS_AS_STRING()
template <typename T, typename SFINAE>
std::string SMF_call_counter<T, SFINAE>::all_counts_as_string() {
    const char nl{'\n'};
    std::string description;
    description.append(
        detail::Default_cstr_counter<T>::default_cstr_count_as_string() + nl);
    description.append(
        detail::Constructor_counter<T>::constructor_counts_as_string() + nl);
    description.append(
        detail::Copy_cstr_counter<T>::copy_cstr_count_as_string() + nl);
    description.append(
        detail::Move_cstr_counter<T>::move_cstr_count_as_string() + nl);
    description.append(
        detail::Copy_assignment_counter<T>::copy_assignment_count_as_string() +
        nl);
    description.append(
        detail::Move_assignment_counter<T>::move_assignment_count_as_string() +
        nl);
    description.append(
        detail::Destructor_counter<T>::destructor_count_as_string());
    return description;
}

}  // namespace utility
#endif  // UTILITY_SMF_CALL_COUNTER_CLASS_HPP
