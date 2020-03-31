#ifndef UTILITIES_LOG_HPP
#define UTILITIES_LOG_HPP
#include <chrono>
#include <cstddef>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include <utility/duration_view.hpp>

namespace utility {

template <typename Stream_t>
class Basic_log : public Stream_t {
   public:
    /// Create Log with parameters passed to Stream_t.
    template <typename... Args>
    Basic_log(Args&&... args) : Stream_t{std::forward<Args>(args)...}
    {}

    /// Constructor overload for default parameters to std::ofstream.
    Basic_log(std::string filename         = "log.txt",
              std::ios_base::openmode mode = std::ios_base::app)
        : Stream_t{std::move(filename), mode}
    {}

    /// Constructor overload for default parameters to std::ofstream.
    Basic_log(char const* filename,
              std::ios_base::openmode mode = std::ios_base::app)
        : Stream_t{filename, mode}
    {}

    /// Sets the number of spaces for labels.
    void set_width(std::size_t width) { width_ = width; }

    /// Outputs 80 char line and blank space.
    void line_break()
    {
        *this << std::setfill('-') << std::setw(80) << '-' << '\n'
              << std::endl
              << std::setfill(' ');
    }

    /// Outputs the current date and time on a single line.
    void timestamp()
    {
        auto const now   = std::chrono::system_clock::now();
        auto const now_t = std::chrono::system_clock::to_time_t(now);
        *this << std::put_time(std::localtime(&now_t), "%c") << std::endl;
    }

    /// Outputs a formatted label and value with spacing determined by width.
    template <typename T>
    void value(std::string const& label, T const& value)
    {
        *this << std::left << std::setw(width_) << label << value << std::endl;
    }

    /// Mark the beginning of the timer.
    void start_timer() { timer_start_ = Clock_t::now(); }

    /// Mark the end of the timer.
    void end_timer() { timer_end_ = Clock_t::now(); }

    /// Output the duration of the timer in units of Duration_t.
    template <typename Duration_t = std::chrono::nanoseconds>
    void output_timer(bool separators = true)
    {
        *this << utility::duration_view<Duration_t>(timer_end_ - timer_start_,
                                                    separators);
    }

    /// Output the duration of the timer in units determined by digit_limit.
    void output_timer(int digit_limit, bool separators = true)
    {
        *this << utility::duration_view(timer_end_ - timer_start_, digit_limit,
                                        separators);
    }

   private:
    using Clock_t      = std::chrono::high_resolution_clock;
    using Time_point_t = std::chrono::time_point<Clock_t>;

    std::size_t width_{15};
    Time_point_t timer_start_;
    Time_point_t timer_end_;
};

using Log            = Basic_log<std::ofstream>;
inline auto log_cout = Log{std::cout.rdbuf()};
inline auto log_cerr = Log{std::cerr.rdbuf()};
inline auto log_clog = Log{std::clog.rdbuf()};

}  // namespace utility
#endif  // UTILITIES_LOG_HPP
