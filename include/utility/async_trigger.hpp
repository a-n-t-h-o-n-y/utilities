#ifndef UTILITY_ASYNC_TRIGGER_HPP
#define UTILITY_ASYNC_TRIGGER_HPP
#include <atomic>
#include <functional>
#include <future>
#include <thread>

#include <signals/signals.hpp>

namespace utility {

// WIP.

/// Provides a Signal which is called periodically in a separate thread.
/// Requires sig::Signals library and pthread. Period has nanosecond resolution.
/// The period is able to vary on each call determined by a function passed
/// in by the client.
class Async_trigger {
   public:
    /// Resolution of period.
    using Duration_t = std::chrono::nanoseconds;

    /// Initialize with a specific period.
    Async_trigger(Duration_t period) : func_{[period] { return period; }} {}

    /// Initialize with a specific period.
    Async_trigger(const std::function<Duration_t()>& period_function)
        : func_{period_function} {}

    // Async_trigger(Async_trigger&&) = default;
    // Async_trigger& operator=(Async_trigger&&) = default;

    /// Sends a stop signal and waits for the last call of trigger() to return.
    ~Async_trigger() { this->stop(); }

    /// Starts the periodic triggering in a separate thread. returns
    /// immediately.
    void start() {
        if (looping_) {
            return;
        }
        looping_ = true;
        future_ = std::async([this] { this->loop(); });
    }

    /// Sends a stop signal for the async trigger thread. Will stop after
    /// current trigger() call is finished.
    void stop() { looping_ = false; }

    /// Change the period between calls to trigger() to a static Duration_t.
    void set_period(Duration_t period) {
        std::lock_guard<std::mutex> guard{func_mutex_};
        func_ = [period] { return period; };
    }

    /// Specify a function that determines the duration of the period, called on
    /// each iteration. Allows for variable period.
    void set_period(const std::function<Duration_t()>& period_function) {
        std::lock_guard<std::mutex> guard{func_mutex_};
        func_ = period_function;
    }

    /// Returns the period's duration.
    Duration_t get_period() const {
        std::lock_guard<std::mutex> guard{func_mutex_};
        return func_();
    }

    /// Returns a reference to the function that determines the period.
    std::function<Duration_t()>& get_period_function() { return func_; }

    /// Returns a copy of the function that determines the period.
    std::function<Duration_t()> get_period_function() const {
        std::lock_guard<std::mutex> guard{func_mutex_};
        return func_;
    }

    /// trigger Signal will be called once every period. This is where Slots
    /// can be attached. Is thread safe.
    sig::Signal<void()> trigger;

    /// Destructor will wait on this future.
    std::future<void> future_;

   private:
    std::function<Duration_t()> func_;
    mutable std::mutex func_mutex_;

    std::atomic_bool looping_{false};

    // fps to duration for cppurses::animation_engine
    // auto tpf = std::chrono::milliseconds((int)((1.0 / (double)rate_) *
    // 1'000));
    void loop() {
        while (looping_) {
            auto begin = std::chrono::high_resolution_clock::now();
            Duration_t period = func_();
            func_mutex_.lock();
            trigger();
            func_mutex_.unlock();
            auto end = std::chrono::high_resolution_clock::now();
            auto trigger_duration = end - begin;
            auto time_left = period - trigger_duration;
            if (time_left > time_left.zero()) {
                std::this_thread::sleep_for(time_left);
            }
        }
    }
};

}  // namespace utility
#endif  // UTILITY_ASYNC_TRIGGER_HPP
