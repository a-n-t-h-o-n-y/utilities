#ifndef UTILITY_DETAIL_SMF_COUNTER_DIRECT_CSTR_COUNTER_HPP
#define UTILITY_DETAIL_SMF_COUNTER_DIRECT_CSTR_COUNTER_HPP
#include <map>
#include <string>
#include <vector>

#include <utility/count_t.hpp>
#include <utility/type_info.hpp>

namespace utility::detail {

/// Provides counting operations for direct initialization of objects
/** Including aggregate initialization. */
template <typename T>
class Direct_cstr_counter {
   private:
    using Parameter_list = std::vector<utility::Type_info>;

   public:
    /// Increment the counter for a specific constructor by one
    /** Identified by the types passed to the constructor's parameter list.
     *  Should be called by the class inheriting this class in the constructor.
     *  */
    template <typename... Args>
    static void increment_direct_cstr_count()
    {
        auto const parameters =
            Parameter_list{utility::get_type_info<Args>()...};
        if (direct_cstr_counts_.count(parameters) == 1)
            ++direct_cstr_counts_.at(parameters);
        else
            direct_cstr_counts_[parameters] = 1;
    }

    /// Retrieve counts of a specific constructor by parameter types.
    /** Constructor counts are held by the types passed to the constructor and
     *  are not necessarily the exact types in the constructor signature. */
    template <typename... Args>
    static auto get_direct_cstr_count() -> Count_t
    {
        auto const parameters =
            Parameter_list{utility::get_type_info<Args>()...};
        auto total = Count_t{0};
        if (direct_cstr_counts_.count(parameters) == 1)
            total = direct_cstr_counts_.at(parameters);
        return total;
    }

    /// Retrieves the total count of all direct constructions.
    static auto get_direct_cstr_counts() -> Count_t
    {
        auto total = Count_t{0};
        for (auto const& parameter_count : direct_cstr_counts_)
            total += parameter_count.second;
        return total;
    }

    /// Set count of a specific constructor to zero.
    /** Constructor identified by the types passed to the constructor's
     *  parameter list. */
    template <typename... Args>
    static void reset_direct_cstr_count()
    {
        auto const parameters =
            Parameter_list{utility::get_type_info<Args>()...};
        if (direct_cstr_counts_.count(parameters) == 1)
            direct_cstr_counts_.erase(direct_cstr_counts_.find(parameters));
    }

    /// Set count of all direct constructors to zero.
    static void reset_direct_cstr_counts() { direct_cstr_counts_.clear(); }

    /// Generate string with count info for a specific constructor.
    /** Identified by the types passed to the constructor's parameter list.
     */
    template <typename... Args>
    static auto direct_cstr_count_as_string() -> std::string
    {
        auto const parameters =
            Parameter_list{utility::get_type_info<Args>()...};
        auto description = utility::get_type_info<T>().full_type_name();
        description.append("{");
        auto comma_separator = std::string{""};
        for (auto const& type_name : parameters) {
            description.append(comma_separator);
            description.append(type_name);
            comma_separator = ", ";
        }
        description.append("}");
        description.append(" called ");
        if (direct_cstr_counts_.count(parameters) == 1) {
            description.append(
                std::to_string(direct_cstr_counts_.at(parameters)));
        }
        else
            description.append("0");
        description.append(" times.");
        return description;
    }

    /// Generate string with count info for all direct constructors.
    static auto direct_cstr_counts_as_string() -> std::string
    {
        auto description = std::string{""};
        for (auto const& parameter_count : direct_cstr_counts_) {
            description.append(utility::get_type_info<T>());
            description.append("{");
            auto comma_separator = std::string{""};
            for (auto const& type_name : parameter_count.first) {
                description.append(comma_separator);
                description.append(type_name);
                comma_separator = ", ";
            }
            description.append("} called ");
            description.append(std::to_string(parameter_count.second));
            description.append(" times.\n");
        }
        if (!description.empty())
            description.pop_back();
        return description;
    }

   private:
    static inline auto direct_cstr_counts_ =
        std::map<Parameter_list, Count_t>{};
};

}  // namespace utility::detail
#endif  // UTILITY_DETAIL_SMF_COUNTER_DIRECT_CSTR_COUNTER_HPP
