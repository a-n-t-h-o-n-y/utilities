#ifndef UTILITY_SMF_CALL_COUNTER_BUILTIN_HPP
#define UTILITY_SMF_CALL_COUNTER_BUILTIN_HPP
#include <string>
#include <type_traits>
#include <utility>

#include <utility/detail/smf_counter/copy_assignment_counter.hpp>
#include <utility/detail/smf_counter/copy_cstr_counter.hpp>
#include <utility/detail/smf_counter/default_cstr_counter.hpp>
#include <utility/detail/smf_counter/destructor_counter.hpp>

namespace utility {

template <typename T>
using Is_builtin = typename std::enable_if<
    std::conjunction<std::negation<std::is_class<T>>,
                     std::negation<std::is_array<T>>>::value>::type;

/// Specialization for Built-in types which are not arrays.
template <typename T>
class SMF_call_counter<T, Is_builtin<T>>
    : public detail::Default_cstr_counter<T>,
      public detail::Copy_cstr_counter<T>,
      public detail::Copy_assignment_counter<T>,
      public detail::Destructor_counter<T> {
   public:
    /// Increment the Default Constructor counter and default construct T.
    SMF_call_counter();

    /// Increment the Copy Constructor counter and copy construct T from value.
    template <typename U>
    SMF_call_counter(const U& value);

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(const SMF_call_counter& other);

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(const T& value);

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(const SMF_call_counter& other);

    /// Increment the Destructor counter and call ~T().
    ~SMF_call_counter();

    /// Conversion to const T&
    operator const T&() const;

    /// Conversion to T&
    operator T&();

    /// Set all counts to zero.
    static void reset_counts();

    /// Generate string with count info for all Special Member Functions.
    static std::string all_counts_as_string();

   private:
    T value_;
};

// IMPLEMENTATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DEFAULT CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_builtin<T>>::SMF_call_counter() {
    detail::Default_cstr_counter<T>::increment_default_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
template <typename U>
SMF_call_counter<T, Is_builtin<T>>::SMF_call_counter(const U& value)
    : value_(value) {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_builtin<T>>::SMF_call_counter(
    const SMF_call_counter& other)
    : value_{other.value_} {
    detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
}

// COPY ASSIGNMENT OPERATOR
template <typename T>
SMF_call_counter<T, Is_builtin<T>>& SMF_call_counter<T, Is_builtin<T>>::
operator=(const T& value) {
    value_ = value;
    detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
    return *this;
}

// COPY ASSIGNMENT OPERATOR
template <typename T>
SMF_call_counter<T, Is_builtin<T>>& SMF_call_counter<T, Is_builtin<T>>::
operator=(const SMF_call_counter& other) {
    value_ = other.value_;
    detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
    return *this;
}

// DESTRUCTOR
template <typename T>
SMF_call_counter<T, Is_builtin<T>>::~SMF_call_counter() {
    detail::Destructor_counter<T>::increment_destructor_count();
}

// OPERATOR CONST T&
template <typename T>
SMF_call_counter<T, Is_builtin<T>>::operator const T&() const {
    return value_;
}

// OPERATOR T&
template <typename T>
SMF_call_counter<T, Is_builtin<T>>::operator T&() {
    return value_;
}

// RESET_COUNTS()
template <typename T>
void SMF_call_counter<T, Is_builtin<T>>::reset_counts() {
    detail::Default_cstr_counter<T>::reset_default_cstr_count();
    detail::Copy_cstr_counter<T>::reset_copy_cstr_count();
    detail::Copy_assignment_counter<T>::reset_copy_assignment_count();
    detail::Destructor_counter<T>::reset_destructor_count();
}

// ALL_COUNTRS_AS_STRING()
template <typename T>
std::string SMF_call_counter<T, Is_builtin<T>>::all_counts_as_string() {
    const char nl{'\n'};
    std::string description;
    description.append(
        detail::Default_cstr_counter<T>::default_cstr_count_as_string() + nl);
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
#endif  // UTILITY_SMF_CALL_COUNTER_BUILTIN_HPP
