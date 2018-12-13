#ifndef UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_CLASS_HPP
#define UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_CLASS_HPP
#include <string>
#include <type_traits>
#include <utility>

#include "../conjunction.hpp"
#include "assignment_counter.hpp"
#include "copy_assignment_counter.hpp"
#include "copy_cstr_counter.hpp"
#include "default_cstr_counter.hpp"
#include "destructor_counter.hpp"
#include "direct_cstr_counter.hpp"
#include "move_assignment_counter.hpp"
#include "move_cstr_counter.hpp"
#include "smf_call_counter_fwd.hpp"

namespace utility {

template <typename T>
using Is_class = typename std::enable_if<
    detail::Conjunction<std::is_class<T>,
                        std::negation<std::is_aggregate<T>>>::value>::type;

/// Specialization for Non-aggregate class types.
template <typename T>
class SMF_call_counter<T, Is_class<T>>
    : public T,
      public detail::Default_cstr_counter<T>,
      public detail::Direct_cstr_counter<T>,
      public detail::Copy_cstr_counter<T>,
      public detail::Move_cstr_counter<T>,
      public detail::Copy_assignment_counter<T>,
      public detail::Move_assignment_counter<T>,
      public detail::Assignment_counter<T>,
      public detail::Destructor_counter<T> {
   public:
    /// Increment the Default Constructor counter and default construct T.
    SMF_call_counter();

    /// Increment the Direct Cnstr counter for Args and construct T with args...
    template <typename... Args>
    SMF_call_counter(Args&&... args);

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(const SMF_call_counter& other);

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(SMF_call_counter& other);

    /// Increment the Copy Constructor counter and copy construct T from value.
    SMF_call_counter(const T& value);

    /// Increment the Copy Constructor counter and copy construct T from value.
    SMF_call_counter(T& value);

    /// Increment the Move Constructor counter and move construct T from value.
    SMF_call_counter(T&& value);

    /// Increment the Move Constructor counter and move construct T from other.
    SMF_call_counter(SMF_call_counter&& other);

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(const SMF_call_counter& other);

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(SMF_call_counter& other);

    /// Increment the Move Assignment counter and call T::operator=(T&&).
    SMF_call_counter& operator=(SMF_call_counter&& other);

    /// Increment the (miscellaneous)Assignment Operator count.
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
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter() {
    detail::Default_cstr_counter<T>::increment_default_cstr_count();
}

// MISCELLANEOUS CONSTRUCTOR
template <typename T>
template <typename... Args>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(Args&&... args)
    : T(std::forward<Args>(args)...) {
    detail::Direct_cstr_counter<T>::template increment_direct_cstr_count<
        Args...>();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(
    const SMF_call_counter& other)
    : T{other} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
// Supresses the variadic template from handling non-const copies.
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(SMF_call_counter& other)
    : SMF_call_counter{const_cast<const SMF_call_counter&>(other)} {}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(const T& value) : T{value} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(T& value) : T{value} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// MOVE CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(T&& value)
    : T{std::move(value)} {
    detail::Move_cstr_counter<T>::increment_move_cstr_count();
}

// MOVE CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_class<T>>::SMF_call_counter(SMF_call_counter&& other)
    : T{std::move(other)} {
    detail::Move_cstr_counter<T>::increment_move_cstr_count();
}

// COPY ASSIGNMENT OPERATOR
// Self-Assignment is counted as a call.
template <typename T>
SMF_call_counter<T, Is_class<T>>& SMF_call_counter<T, Is_class<T>>::operator=(
    const SMF_call_counter& other) {
    T::operator=(other);
    detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
    return *this;
}

// Supresses template from handling non-const assignments.
template <typename T>
SMF_call_counter<T, Is_class<T>>& SMF_call_counter<T, Is_class<T>>::operator=(
    SMF_call_counter& other) {
    return this->operator=(const_cast<const SMF_call_counter&>(other));
}

// MOVE ASSIGNMENT OPERATOR
// Self-Assignment is counted as a call.
template <typename T>
SMF_call_counter<T, Is_class<T>>& SMF_call_counter<T, Is_class<T>>::operator=(
    SMF_call_counter&& other) {
    T::operator=(std::move(other));
    detail::Move_assignment_counter<T>::increment_move_assignment_count();
    return *this;
}

// ASSIGNMENT OPERATOR
template <typename T>
template <typename U>
auto SMF_call_counter<T, Is_class<T>>::operator=(U&& other) {
    detail::Assignment_counter<T>::template increment_assignment_count<U>();
    return T::operator=(std::forward<U>(other));
}

// DESTRUCTOR
template <typename T>
SMF_call_counter<T, Is_class<T>>::~SMF_call_counter() {
    detail::Destructor_counter<T>::increment_destructor_count();
}

// RESET_COUNTS()
template <typename T>
void SMF_call_counter<T, Is_class<T>>::reset_counts() {
    using namespace detail;
    Default_cstr_counter<T>::reset_default_cstr_count();
    Direct_cstr_counter<T>::reset_direct_cstr_counts();
    Copy_cstr_counter<T>::reset_copy_cstr_count();
    Move_cstr_counter<T>::reset_move_cstr_count();
    Copy_assignment_counter<T>::reset_copy_assignment_count();
    Move_assignment_counter<T>::reset_move_assignment_count();
    Assignment_counter<T>::reset_assignment_counts();
    Destructor_counter<T>::reset_destructor_count();
}

// ALL_COUNTS_AS_STRING()
template <typename T>
std::string SMF_call_counter<T, Is_class<T>>::all_counts_as_string() {
    const auto nl = '\n';
    auto description = std::string{""};
    using namespace detail;
    description.append(Default_cstr_counter<T>::default_cstr_count_as_string() +
                       nl);
    description.append(Direct_cstr_counter<T>::direct_cstr_counts_as_string() +
                       nl);
    description.append(Copy_cstr_counter<T>::copy_cstr_count_as_string() + nl);
    description.append(Move_cstr_counter<T>::move_cstr_count_as_string() + nl);
    description.append(
        Copy_assignment_counter<T>::copy_assignment_count_as_string() + nl);
    description.append(
        Move_assignment_counter<T>::move_assignment_count_as_string() + nl);
    description.append(Assignment_counter<T>::Assignment_counts_as_string() +
                       nl);
    description.append(Destructor_counter<T>::destructor_count_as_string());
    return description;
}

}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_CLASS_HPP
