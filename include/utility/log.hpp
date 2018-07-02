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
    Basic_log(Args&&... args) : Stream_t{std::forward<Args>(args)...} {}

    /// Constructor overload for default parameters to std::ofstream.
    Basic_log(const std::string filename = "log.txt",
              std::ios_base::openmode mode = std::ios_base::app)
        : Stream_t{filename, mode} {}

    /// Constructor overload for default parameters to std::ofstream.
    Basic_log(const char* filename,
              std::ios_base::openmode mode = std::ios_base::app)
        : Stream_t{filename, mode} {}

    /// Sets the number of spaces for labels.
    void set_width(std::size_t width) { width_ = width; }

    /// Outputs 80 char line and blank space.
    void line_break() {
        *this << std::setfill('-') << std::setw(80) << '-' << '\n'
              << std::endl
              << std::setfill(' ');
    }

    /// Outputs the current date and time on a single line.
    void timestamp() {
        auto now = std::chrono::system_clock::now();
        auto now_t = std::chrono::system_clock::to_time_t(now);
        *this << std::put_time(std::localtime(&now_t), "%c") << std::endl;
    }

    /// Outputs a formatted label and value with spacing determined by width.
    template <typename T>
    void value(const std::string& label, const T& value) {
        *this << std::left << std::setw(width_) << label << value << std::endl;
    }

    /// Mark the beginning of the timer.
    void start_timer() { timer_start_ = clock_t::now(); }

    /// Mark the end of the timer.
    void end_timer() { timer_end_ = clock_t::now(); }

    /// Output the duration of the timer in units of Duration_t.
    template <typename Duration_t = std::chrono::nanoseconds>
    void output_timer(bool seperators = true) {
        *this << utility::duration_view<Duration_t>(timer_end_ - timer_start_,
                                                    seperators);
    }

    /// Output the duration of the timer in units determined by digit_limit.
    void output_timer(int digit_limit, bool seperators = true) {
        *this << utility::duration_view(timer_end_ - timer_start_, digit_limit,
                                        seperators);
    }

   private:
    using clock_t = std::chrono::high_resolution_clock;

    std::size_t width_{15};
    std::chrono::time_point<clock_t> timer_start_;
    std::chrono::time_point<clock_t> timer_end_;
};

using Log = Basic_log<std::ofstream>;
Basic_log<std::ostream> log_cout{std::cout.rdbuf()};
Basic_log<std::ostream> log_cerr{std::cerr.rdbuf()};
Basic_log<std::ostream> log_clog{std::clog.rdbuf()};

}  // namespace utility
#endif  // UTILITIES_LOG_HPP
