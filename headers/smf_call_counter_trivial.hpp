#ifndef UTILITY_SMF_CALL_COUNTER_TRIVIAL_HPP
#define UTILITY_SMF_CALL_COUNTER_TRIVIAL_HPP
#include <string>
#include <type_traits>
#include <utility>

#include "count_t.hpp"
#include "detail/copy_assignment_counter.hpp"
#include "detail/copy_cstr_counter.hpp"
#include "detail/default_cstr_counter.hpp"
#include "detail/destructor_counter.hpp"

namespace detail {

template <typename T>
using Is_trivial_and_not_array =
    std::conjunction<std::is_trivial<T>, std::negation<std::is_array<T>>>;

template <typename T>
inline constexpr bool is_trivial_and_not_array_v =
    Is_trivial_and_not_array<T>::value;

}  // namespace detail

template <typename T>
using Enable_if_trivial_and_not_array =
    typename std::enable_if_t<detail::is_trivial_and_not_array_v<T>>;

namespace utility {
/// Specialization for Trivial types which are not arrays.
template <typename T>
class SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>
    : public detail::Default_cstr_counter<T>,
      public detail::Constructor_counter<T>,
      public detail::Copy_cstr_counter<T>,
      public detail::Copy_assignment_counter<T> {
   public:
    /// Increment the Default Constructor counter and default construct T.
    SMF_call_counter();

    /// Increment the Constructor counter for Args and construct T with
    /// args... For aggregate initialization.
    template <typename... Args>
    SMF_call_counter(Args&&... args);

    /// Increment the Copy Constructor counter and copy construct T from
    /// value.
    SMF_call_counter(const T& value);

    /// Increment the Copy Constructor counter and copy construct T from
    /// value.
    SMF_call_counter(T& value);

    /// Increment the Copy Constructor counter and copy construct T from
    /// other.
    SMF_call_counter(const SMF_call_counter& other);

    /// Increment the Copy Constructor counter and copy construct T from
    /// other.
    SMF_call_counter(SMF_call_counter& other);

    /// Increment the Copy Constructor counter and copy construct T from
    /// other. Overloaded so variadic template does not get called.
    SMF_call_counter(T&& value);

    /// No Move Construction for Trivial types.
    SMF_call_counter(SMF_call_counter&&) = delete;

    /// Increment the Copy Assignment counter and call T::operator=(const
    /// T&).
    SMF_call_counter& operator=(const T& value);

    /// Increment the Copy Assignment counter and call T::operator=(const
    /// T&).
    SMF_call_counter& operator=(const SMF_call_counter& other);

    /// No Move Assignment Operator for Trivial types.
    SMF_call_counter& operator=(SMF_call_counter&&) = delete;

    /// Increment the Destructor counter and call ~T().
    ~SMF_call_counter();

    /// Conversion to const T&
    operator const T&();

    /// Conversion to T&
    operator T&();

    /// Set all counts to zero.
    static void reset_counts();

    /// Generate string with count info for all Special Member Functions.
    static std::string all_counts_as_string();

   private:
    T value_;
};

// DEFAULT CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter() {
    detail::Default_cstr_counter<T>::increment_default_cstr_count();
}

// AGGREGATE CONSTRUCTOR
template <typename T>
template <typename... Args>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter(
    Args&&... args)
    : value_(std::forward<Args>(args)...) {
    detail::Constructor_counter<T>::template increment_constructor_count<
        Args...>();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter(
    const T& value)
    : value_{value} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter(
    T& value)
    : value_{value} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter(
    const SMF_call_counter& other)
    : value_{other.value_} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter(
    SMF_call_counter& other)
    : value_{other.value_} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::SMF_call_counter(
    T&& value)
    : value_{value} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY ASSIGNMENT OPERATOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>&
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::operator=(
    const T& value) {
    value_ = value;
    detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
    return *this;
}

// COPY ASSIGNMENT OPERATOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>&
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::operator=(
    const SMF_call_counter& other) {
    value_ = other.value_;
    detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
    return *this;
}

// DESTRUCTOR
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::~SMF_call_counter() {
    detail::Destructor_counter<T>::increment_destructor_count();
}

// OPERATOR CONST T&
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::operator const T&() {
    return value_;
}

// OPERATOR T&
template <typename T>
SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::operator T&() {
    return value_;
}

// RESET_COUNTS()
template <typename T>
void SMF_call_counter<T, Enable_if_trivial_and_not_array<T>>::reset_counts() {
    detail::Default_cstr_counter<T>::reset_default_cstr_count();
    detail::Constructor_counter<T>::reset_constructor_counts();
    detail::Copy_cstr_counter<T>::reset_copy_cstr_count();
    detail::Copy_assignment_counter<T>::reset_copy_assignment_count();
}

// ALL_COUNTRS_AS_STRING()
template <typename T>
std::string
SMF_call_counter<T,
                 Enable_if_trivial_and_not_array<T>>::all_counts_as_string() {
    const char nl{'\n'};
    std::string description;
    description.append(
        detail::Default_cstr_counter<T>::default_cstr_count_as_string() + nl);
    description.append(
        detail::Constructor_counter<T>::constructor_counts_as_string() + nl);
    description.append(
        detail::Copy_cstr_counter<T>::copy_cstr_count_as_string() + nl);
    description.append(
        detail::Copy_assignment_counter<T>::copy_assignment_count_as_string() +
        nl);
    description.append(
        detail::Destructor_counter<T>::destructor_count_as_string());
    return description;
}

}  // namespace utility
#endif  // UTILITY_SMF_CALL_COUNTER_TRIVIAL_HPP
