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
    SMF_call_counter();

    /// Increments the Initializer List Constructor count and initializes array.
    template <typename... Args>
    SMF_call_counter(Args&&... args);

    SMF_call_counter(const SMF_call_counter& other) = delete;
    SMF_call_counter(SMF_call_counter&& other) = delete;
    SMF_call_counter& operator=(const SMF_call_counter& other) = delete;
    SMF_call_counter& operator=(SMF_call_counter&& other) = delete;

    /// Increments the Destructor count.
    ~SMF_call_counter();

    /// Non-explicit converstions to const T&.
    operator const T&() const;

    /// Non-explicit converstions to T&.
    operator T&();

    /// Set all counts to zero.
    static void reset_counts();

    /// Generate string with count info for all Special Member Functions.
    static std::string all_counts_as_string();

   private:
    T array_;
};

// IMPLEMENTATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DEFAULT CONSTRUCTOR
template <typename T>
SMF_call_counter<T, Is_array<T>>::SMF_call_counter() {
    detail::Default_cstr_counter<T>::increment_default_cstr_count();
}

// INITIALIZER LIST CONSTRUCTOR
template <typename T>
template <typename... Args>
SMF_call_counter<T, Is_array<T>>::SMF_call_counter(Args&&... args)
    : array_{std::forward<Args>(args)...} {
    detail::Initializer_list_cstr_counter<
        T>::increment_initializer_list_cstr_count();
}

// DESTRUCTOR
template <typename T>
SMF_call_counter<T, Is_array<T>>::~SMF_call_counter() {
    detail::Destructor_counter<T>::increment_destructor_count();
}

// const T& CONVERSION
template <typename T>
SMF_call_counter<T, Is_array<T>>::operator const T&() const {
    return array_;
}

// T& CONVERSION
template <typename T>
SMF_call_counter<T, Is_array<T>>::operator T&() {
    return array_;
}

// RESET_COUNTS()
template <typename T>
void SMF_call_counter<T, Is_array<T>>::reset_counts() {
    using namespace detail;
    Default_cstr_counter<T>::reset_default_cstr_count();
    Initializer_list_cstr_counter<T>::reset_initializer_list_cstr_count();
    Destructor_counter<T>::reset_destructor_count();
}

// ALL_COUNTS_AS_STRING()
template <typename T>
std::string SMF_call_counter<T, Is_array<T>>::all_counts_as_string() {
    const auto nl = '\n';
    auto description = std::string{""};
    using namespace detail;
    description.append(Default_cstr_counter<T>::default_cstr_count_as_string() +
                       nl);
    description.append(Initializer_list_cstr_counter<
                           T>::initializer_list_cstr_count_as_string() +
                       nl);
    description.append(Destructor_counter<T>::destructor_count_as_string());
    return description;
}

}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_SMF_CALL_COUNTER_ARRAY_HPP
