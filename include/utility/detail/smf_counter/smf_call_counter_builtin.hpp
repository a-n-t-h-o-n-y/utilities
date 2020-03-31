#ifndef UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_BUILTIN_HPP
#define UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_BUILTIN_HPP
#include <string>
#include <type_traits>

#include "../conjunction.hpp"
#include "copy_assignment_counter.hpp"
#include "copy_cstr_counter.hpp"
#include "default_cstr_counter.hpp"
#include "destructor_counter.hpp"
#include "smf_call_counter_fwd.hpp"

namespace utility {

template <typename T>
using Is_builtin = typename std::enable_if<
    detail::Conjunction<std::negation<std::is_class<T>>,
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
    SMF_call_counter()
    {
        detail::Default_cstr_counter<T>::increment_default_cstr_count();
    }

    /// Increment the Copy Constructor counter and copy construct T from value.
    template <typename U>
    SMF_call_counter(U const& value) : value_(value)
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(SMF_call_counter const& other) : value_{other.value_}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(T const& value)
    {
        value_ = value;
        detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
        return *this;
    }

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(SMF_call_counter const& other)
    {
        value_ = other.value_;
        detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
        return *this;
    }

    /// Increment the Destructor counter and call ~T().
    ~SMF_call_counter()
    {
        detail::Destructor_counter<T>::increment_destructor_count();
    }

    /// Conversion to const T&
    operator T const&() const { return value_; }

    /// Conversion to T&
    operator T&() { return value_; }

    /// Set all counts to zero.
    static void reset_counts()
    {
        using namespace detail;
        Default_cstr_counter<T>::reset_default_cstr_count();
        Copy_cstr_counter<T>::reset_copy_cstr_count();
        Copy_assignment_counter<T>::reset_copy_assignment_count();
        Destructor_counter<T>::reset_destructor_count();
    }

    /// Generate string with count info for all Special Member Functions.
    static auto all_counts_as_string() -> std::string
    {
        auto const nl    = '\n';
        auto description = std::string{""};
        using namespace detail;
        description.append(
            Default_cstr_counter<T>::default_cstr_count_as_string() + nl);
        description.append(Copy_cstr_counter<T>::copy_cstr_count_as_string() +
                           nl);
        description.append(
            Copy_assignment_counter<T>::copy_assignment_count_as_string() + nl);
        description.append(Destructor_counter<T>::destructor_count_as_string());
        return description;
    }

   private:
    T value_;
};

}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_BUILTIN_HPP
