#ifndef UTILITY_DETAIL_SMF_COUNTER_ASSIGNMENT_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_ASSIGNMENT_COUNTER_HPP
#include <map>
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility {
namespace detail {

template <typename T>
class Assignment_counter {
   public:
    /// Increment the counter for a specific assignment by one.
    /** Identified by the type passed to the operator's parameter list. Should
     *  be called by the class inheriting this class in the operator=()
     *  overload. */
    template <typename U>
    static void increment_assignment_count();

    /// Retrieve counts of a specific assignment operator by parameter type.
    /** Assignment counts are held by the type passed to the operator and
     *  is not necessarily the exact type in the constructor signature.*/
    template <typename U>
    static Count_t get_assignment_count();

    /// Retrieves the total count of all miscellaneous assignment operators.
    static Count_t get_assignment_counts();

    /// Set count of a specific assignment operator to zero.
    /** Operator identified by the type passed to the operator's parameter list.
     *  */
    template <typename U>
    static void reset_assignment_count();

    /// Set count of all miscellaneous assignment operators to zero.
    static void reset_assignment_counts();

    /// Generate string with count info for a specific assignment operator.
    /** Identified by the type passed to the operator's parameter list. */
    template <typename U>
    static std::string assignment_count_as_string();

    /// Make string with count info for all miscellaneous assignement operators.
    static std::string assignment_counts_as_string();

   private:
    static std::map<utility::Type_info, Count_t> assignment_counts_;
};

template <typename T>
std::map<utility::Type_info, Count_t> Assignment_counter<T>::assignment_counts_;

template <typename T>
template <typename U>
void Assignment_counter<T>::increment_assignment_count() {
    const auto parameter_type = utility::get_type_info<U>();
    if (assignment_counts_.count(parameter_type) == 1) {
        ++assignment_counts_.at(parameter_type);
    } else {
        assignment_counts_[parameter_type] = 1;
    }
}

template <typename T>
template <typename U>
Count_t Assignment_counter<T>::get_assignment_count() {
    const auto parameter_type = utility::get_type_info<U>();
    auto total = Count_t{0};
    if (assignment_counts_.count(parameter_type) == 1) {
        total = assignment_counts_.at(parameter_type);
    }
    return total;
}

template <typename T>
Count_t Assignment_counter<T>::get_assignment_counts() {
    auto total = Count_t{0};
    for (const auto& parameter_count : assignment_counts_) {
        total += parameter_count.second;
    }
    return total;
}

template <typename T>
template <typename U>
void Assignment_counter<T>::reset_assignment_count() {
    const auto parameter_type = utility::get_type_info<U>();
    if (assignment_counts_.count(parameter_type) == 1) {
        assignment_counts_.erase(assignment_counts_.find(parameter_type));
    }
}

template <typename T>
void Assignment_counter<T>::reset_assignment_counts() {
    assignment_counts_.clear();
}

template <typename T>
template <typename U>
std::string Assignment_counter<T>::assignment_count_as_string() {
    const auto parameter_type = utility::get_type_info<U>();
    auto description = std::string{utility::get_type_info<T>()};
    description.append("::operator=(");
    description.append(parameter_type);
    description.append(")");
    description.append(" called ");
    if (assignment_counts_.count(parameter_type) == 1) {
        description.append(
            std::to_string(assignment_counts_.at(parameter_type)));
    } else {
        description.append("0");
    }
    description.append(" times.");
    return description;
}

template <typename T>
std::string Assignment_counter<T>::assignment_counts_as_string() {
    auto description = std::string{""};
    for (const auto& parameter_count : assignment_counts_) {
        description.append(std::string{utility::get_type_info<T>()});
        description.append("::operator=(");
        description.append(parameter_count.first);
        description.append(") called ");
        description.append(std::to_string(parameter_count.second));
        description.append(" times.\n");
    }
    if (!description.empty()) {
        description.pop_back();
    }
    return description;
}
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_SMF_COUNTER_ASSIGNMENT_COUNTER_HPP
