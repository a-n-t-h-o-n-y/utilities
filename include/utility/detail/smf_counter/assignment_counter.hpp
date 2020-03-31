#ifndef UTILITY_DETAIL_SMF_COUNTER_ASSIGNMENT_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_ASSIGNMENT_COUNTER_HPP
#include <map>
#include <string>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

template <typename T>
class Assignment_counter {
   public:
    /// Increment the counter for a specific assignment by one.
    /** Identified by the type passed to the operator's parameter list. Should
     *  be called by the class inheriting this class in the operator=()
     *  overload. */
    template <typename U>
    static void increment_assignment_count()
    {
        auto const parameter_type = utility::get_type_info<U>();
        if (assignment_counts_.count(parameter_type) == 1)
            ++assignment_counts_.at(parameter_type);
        else
            assignment_counts_[parameter_type] = 1;
    }

    /// Retrieve counts of a specific assignment operator by parameter type.
    /** Assignment counts are held by the type passed to the operator and
     *  is not necessarily the exact type in the constructor signature.*/
    template <typename U>
    static auto get_assignment_count() -> Count_t
    {
        auto const parameter_type = utility::get_type_info<U>();
        auto total                = Count_t{0};
        if (assignment_counts_.count(parameter_type) == 1)
            total = assignment_counts_.at(parameter_type);
        return total;
    }

    /// Retrieves the total count of all miscellaneous assignment operators.
    static auto get_assignment_counts() -> Count_t
    {
        auto total = Count_t{0};
        for (auto const& parameter_count : assignment_counts_)
            total += parameter_count.second;
        return total;
    }

    /// Set count of a specific assignment operator to zero.
    /** Operator identified by the type passed to the operator's parameter list.
     *  */
    template <typename U>
    static void reset_assignment_count()
    {
        auto const parameter_type = utility::get_type_info<U>();
        if (assignment_counts_.count(parameter_type) == 1)
            assignment_counts_.erase(assignment_counts_.find(parameter_type));
    }

    /// Set count of all miscellaneous assignment operators to zero.
    static void reset_assignment_counts() { assignment_counts_.clear(); }

    /// Generate string with count info for a specific assignment operator.
    /** Identified by the type passed to the operator's parameter list. */
    template <typename U>
    static auto assignment_count_as_string() -> std::string
    {
        auto const parameter_type = utility::get_type_info<U>();
        auto description = utility::get_type_info<T>().full_type_name();
        description.append("::operator=(");
        description.append(parameter_type);
        description.append(")");
        description.append(" called ");
        if (assignment_counts_.count(parameter_type) == 1) {
            description.append(
                std::to_string(assignment_counts_.at(parameter_type)));
        }
        else
            description.append("0");
        description.append(" times.");
        return description;
    }

    /// Make string with count info for all miscellaneous assignement operators.
    static auto assignment_counts_as_string() -> std::string
    {
        auto description = std::string{""};
        for (auto const& parameter_count : assignment_counts_) {
            description.append(utility::get_type_info<T>().full_type_name());
            description.append("::operator=(");
            description.append(parameter_count.first);
            description.append(") called ");
            description.append(std::to_string(parameter_count.second));
            description.append(" times.\n");
        }
        if (!description.empty())
            description.pop_back();
        return description;
    }

   private:
    static inline auto assignment_counts_ =
        std::map<utility::Type_info, Count_t>{};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_ASSIGNMENT_COUNTER_HPP
