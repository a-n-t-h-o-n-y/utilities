#ifndef UTILITY_DETAIL_CONSTRUCTOR_COUNTER_HPP
#define UTILITY_DETAIL_CONSTRUCTOR_COUNTER_HPP
#include <map>
#include <string>
#include <vector>

#include "../count_t.hpp"
#include "../type_info.hpp"

namespace utility {
namespace detail {

/// Provides counting operations for constructors that are not the default,
/// copy, or move constructors, called miscellaneous constructors here.
template <typename>
class Constructor_counter {
   public:
    /// Increment the counter for a specific constructor by one, identified by
    /// the types passed to the constructor's parameter list. Should be called
    /// by the class inheriting this class in the constructor.
    template <typename... Args>
    static void increment_constructor_count();

    /// Retrieve counts of a specific constructor by parameter types.
    /// Constructor counts are held by the types passed to the constructor and
    /// are not necessarily the exact types in the constructor signature.
    template <typename... Args>
    static Count_t get_constructor_count();

    /// Retrieves the total count of all miscellaneous constructors.
    static Count_t get_constructor_counts();

    /// Set count of a specific constructor to zero. Constructor identified by
    /// the types passed to the constructor's parameter list.
    template <typename... Args>
    static void reset_constructor_count();

    /// Set count of all miscellaneous constructors to zero.
    static void reset_constructor_counts();

    /// Generate string with count info for a specific constructor, identified
    /// by the types passed to the constructor's parameter list.
    template <typename... Args>
    static std::string constructor_count_as_string();

    /// Generate string with count info for all miscellaneous constructors.
    static std::string constructor_counts_as_string();

   private:
    using Parameter_list = std::vector<utility::Type_info>;
    static std::map<Parameter_list, Count_t> constructor_counts_;
};

template <typename T>
std::map<typename Constructor_counter<T>::Parameter_list, Count_t>
    Constructor_counter<T>::constructor_counts_;

template <typename T>
template <typename... Args>
void Constructor_counter<T>::increment_constructor_count() {
    Parameter_list parameters{utility::get_type_info<Args>()...};
    if (constructor_counts_.count(parameters) == 1) {
        ++constructor_counts_.at(parameters);
    } else {
        constructor_counts_[parameters] = 1;
    }
}

template <typename T>
template <typename... Args>
Count_t Constructor_counter<T>::get_constructor_count() {
    Parameter_list parameters{utility::get_type_info<Args>()...};
    Count_t total{0};
    if (constructor_counts_.count(parameters) == 1) {
        total = constructor_counts_.at(parameters);
    }
    return total;
}

template <typename T>
Count_t Constructor_counter<T>::get_constructor_counts() {
    Count_t total{0};
    for (const auto& parameter_count_pair : constructor_counts_) {
        total += parameter_count_pair.second;
    }
    return total;
}

template <typename T>
template <typename... Args>
void Constructor_counter<T>::reset_constructor_count() {
    Parameter_list parameters{utility::get_type_info<Args>()...};
    if (constructor_counts_.count(parameters) == 1) {
        constructor_counts_.erase(constructor_counts_.find(parameters));
    }
}

template <typename T>
void Constructor_counter<T>::reset_constructor_counts() {
    constructor_counts_.clear();
}

template <typename T>
template <typename... Args>
std::string Constructor_counter<T>::constructor_count_as_string() {
    Parameter_list parameters{utility::get_type_info<Args>()...};
    std::string description{utility::get_type_info<T>()};
    description.append("(");
    std::string comma_seperator;
    for (const utility::Type_info& type_name : parameters) {
        description.append(comma_seperator);
        description.append(type_name);
        comma_seperator = ", ";
    }
    description.append(")");
    description.append(" called ");
    if (constructor_counts_.count(parameters) == 1) {
        description.append(std::to_string(constructor_counts_.at(parameters)));
    } else {
        description.append("0");
    }
    description.append(" times.");
    return description;
}

template <typename T>
std::string Constructor_counter<T>::constructor_counts_as_string() {
    std::string description;
    for (const auto& parameter_count_pair : constructor_counts_) {
        description.append(utility::get_type_info<T>());
        description.append("(");
        std::string comma_seperator;
        for (const Type_info& type_name : parameter_count_pair.first) {
            description.append(comma_seperator);
            description.append(type_name);
            comma_seperator = ", ";
        }
        description.append(") called ");
        description.append(std::to_string(parameter_count_pair.second));
        description.append(" times.\n");
    }
    if (!description.empty()) {
        description.pop_back();
    }
    return description;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_CONSTRUCTOR_COUNTER_HPP
