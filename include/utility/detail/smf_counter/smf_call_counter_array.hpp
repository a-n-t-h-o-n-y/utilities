#ifndef UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_ARRAY_HPP
#define UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_ARRAY_HPP
#include <initializer_list>
#include <string>
#include <type_traits>
#include <utility>

#include "default_cstr_counter.hpp"
#include "destructor_counter.hpp"
#include "initializer_list_cstr_counter.hpp"
#include "smf_call_counter_fwd.hpp"

namespace utility {
template <typename T>
using Is_array = typename std::enable_if_t<std::is_array_v<T>>;

/// Array specialization of Special Member Function Call Counter.
template <typename T>
class SMF_call_counter<T, Is_array<T>>
    : public detail::Default_cstr_counter<T>,
      public detail::Initializer_list_cstr_counter<T>,
      public detail::Destructor_counter<T> {
   public:
    /// Increments the Default Constructor count and default initializes a T.
    SMF_call_counter()
    {
        detail::Default_cstr_counter<T>::increment_default_cstr_count();
    }

    /// Increments the Initializer List Constructor count and initializes array.
    template <typename... Args>
    SMF_call_counter(Args&&... args) : array_{std::forward<Args>(args)...}
    {
        detail::Initializer_list_cstr_counter<
            T>::increment_initializer_list_cstr_count();
    }

    SMF_call_counter(SMF_call_counter const& other) = delete;
    SMF_call_counter(SMF_call_counter&& other)      = delete;
    SMF_call_counter& operator=(SMF_call_counter const& other) = delete;
    SMF_call_counter& operator=(SMF_call_counter&& other) = delete;

    /// Increments the Destructor count.
    ~SMF_call_counter()
    {
        detail::Destructor_counter<T>::increment_destructor_count();
    }

    /// Non-explicit converstions to const T&.
    operator T const&() const { return array_; }

    /// Non-explicit converstions to T&.
    operator T&() { return array_; }
    /// Set all counts to zero.
    static void reset_counts()
    {
        using namespace detail;
        Default_cstr_counter<T>::reset_default_cstr_count();
        Initializer_list_cstr_counter<T>::reset_initializer_list_cstr_count();
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
        description.append(Initializer_list_cstr_counter<
                               T>::initializer_list_cstr_count_as_string() +
                           nl);
        description.append(Destructor_counter<T>::destructor_count_as_string());
        return description;
    }

   private:
    T array_;
};
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_ARRAY_HPP
