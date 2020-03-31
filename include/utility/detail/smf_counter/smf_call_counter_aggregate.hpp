#ifndef UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_AGGREGATE_HPP
#define UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_AGGREGATE_HPP
#include <string>
#include <type_traits>
#include <utility>

#include "../conjunction.hpp"
#include "copy_assignment_counter.hpp"
#include "copy_cstr_counter.hpp"
#include "default_cstr_counter.hpp"
#include "destructor_counter.hpp"
#include "direct_cstr_counter.hpp"
#include "smf_call_counter_fwd.hpp"

namespace utility {

template <typename T>
using Is_aggregate = typename std::enable_if<
    detail::Conjunction<std::is_aggregate<T>,
                        std::negation<std::is_array<T>>>::value>::type;

/// Specialization for aggregate types.
template <typename T>
class SMF_call_counter<T, Is_aggregate<T>>
    : public T,
      public detail::Default_cstr_counter<T>,
      public detail::Direct_cstr_counter<T>,
      public detail::Copy_cstr_counter<T>,
      public detail::Copy_assignment_counter<T>,
      public detail::Destructor_counter<T> {
   public:
    /// Increment the Default Constructor counter and default construct T.
    SMF_call_counter()
    {
        detail::Default_cstr_counter<T>::increment_default_cstr_count();
    }

    /// Increment the Constructor counter for Args and construct T with args...
    /** Aggregate Initialization. */
    template <typename... Args>
    SMF_call_counter(Args&&... args) : T{std::forward<Args>(args)...}
    {
        detail::Direct_cstr_counter<T>::template increment_direct_cstr_count<
            Args...>();
    }

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(SMF_call_counter const& other) : T{other}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Copy Constructor counter and copy construct T from other.
    SMF_call_counter(SMF_call_counter& other) : T{other}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Copy Constructor counter and copy construct T from value.
    SMF_call_counter(T const& value) : T{value}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Copy Constructor counter and copy construct T from value.
    SMF_call_counter(T& value) : T{value}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Move Constructor counter and move construct T from value.
    SMF_call_counter(T&& value) : T{value}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Move Constructor counter and move construct T from other.
    SMF_call_counter(SMF_call_counter&& other) : T{other}
    {
        detail::Copy_cstr_counter<T>::increment_copy_cstr_count();
    }

    /// Increment the Copy Assignment counter and call T::operator=(const T&).
    SMF_call_counter& operator=(SMF_call_counter const& other)
    {
        T::operator=(other);
        detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
        return *this;
    }

    /// Increment the Move Assignment counter and call T::operator=(T&&).
    SMF_call_counter& operator=(SMF_call_counter&& other)
    {
        T::operator=(other);
        detail::Copy_assignment_counter<T>::increment_copy_assignment_count();
        return *this;
    }

    /// Increment the Destructor counter and call ~T().
    ~SMF_call_counter()
    {
        detail::Destructor_counter<T>::increment_destructor_count();
    }

    /// Set all counts to zero.
    static void reset_counts()
    {
        using namespace detail;
        Default_cstr_counter<T>::reset_default_cstr_count();
        Direct_cstr_counter<T>::reset_direct_cstr_counts();
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
        description.append(
            Direct_cstr_counter<T>::direct_cstr_counts_as_string() + nl);
        description.append(Copy_cstr_counter<T>::copy_cstr_count_as_string() +
                           nl);
        description.append(
            Copy_assignment_counter<T>::copy_assignment_count_as_string() + nl);
        description.append(Destructor_counter<T>::destructor_count_as_string());
        return description;
    }
};

}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_AGGREGATE_HPP
