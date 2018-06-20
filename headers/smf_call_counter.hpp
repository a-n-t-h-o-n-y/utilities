#include <cstdint>

namespace utility {

/// Special Member Function Call Counter
///
/// Transparently wraps type T and  counts the number of times each special
/// member function is called.
template <typename T>
class SMF_call_counter : public T {
   public:
    // using T::T;
    // Variadic template that then makes call down explicitly in initializer
    // list to T(params...) then catch all count for 'other constructors' or you
    // can have a dynamic list with type id tuples or something. Maybe not that
    // helpful, but better than nothing?
    // you can hold a map with type_index list as key, count as value. getting
    // the const/volitile-ness in the type is important.
    // access template function: get_count<int, const std::string&>(); will look
    // up those type id's index, in the correct order too, and return the value
    // in the map.
    SMF_call_counter() { ++default_cstr_count_; }
    template <typename... Args>
    SMF_call_counter(Args&&... args) : T{std::forward<Args>(args)...} {
        ++misc_cstr_count_;
    }
    SMF_call_counter(const SMF_call_counter& other) { ++copy_cstr_count_; }
    SMF_call_counter(SMF_call_counter&& other) { ++move_cstr_count_; }
    SMF_call_counter& operator=(const SMF_call_counter& other) {
        T::operator=(other);
        ++copy_assignment_count_;
        return *this;
    }
    SMF_call_counter& operator=(SMF_call_counter&& other) {
        T::operator=(std::forward<SMF_call_counter&&>(other));
        ++move_assignment_count_;
        return *this;
    }
    ~SMF_call_counter() { ++destructor_count_; }

    /// Retrieve counts.
    static std::uint64_t get_default_cstr_count();
    static std::uint64_t get_misc_cstr_count();
    static std::uint64_t get_copy_cstr_count();
    static std::uint64_t get_move_cstr_count();
    static std::uint64_t get_copy_assignment_count();
    static std::uint64_t get_move_assignment_count();
    static std::uint64_t get_destructor_count();

    /// Set all counts to zero.
    static void reset_counts();
    static void reset_default_cstr_count();
    static void reset_misc_cstr_count();
    static void reset_copy_cstr_count();
    static void reset_move_cstr_count();
    static void reset_copy_assignment_count();
    static void reset_move_assignment_count();
    static void reset_destructor_count();

   private:
    static std::uint64_t default_cstr_count_;
    static std::uint64_t misc_cstr_count_;
    static std::uint64_t copy_cstr_count_;
    static std::uint64_t move_cstr_count_;
    static std::uint64_t copy_assignment_count_;
    static std::uint64_t move_assignment_count_;
    static std::uint64_t destructor_count_;
};

template <typename T>
std::uint64_t SMF_call_counter<T>::default_cstr_count_{0};
template <typename T>
std::uint64_t SMF_call_counter<T>::misc_cstr_count_{0};
template <typename T>
std::uint64_t SMF_call_counter<T>::copy_cstr_count_{0};
template <typename T>
std::uint64_t SMF_call_counter<T>::move_cstr_count_{0};
template <typename T>
std::uint64_t SMF_call_counter<T>::copy_assignment_count_{0};
template <typename T>
std::uint64_t SMF_call_counter<T>::move_assignment_count_{0};
template <typename T>
std::uint64_t SMF_call_counter<T>::destructor_count_{0};

// IMPLEMENTATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
std::uint64_t SMF_call_counter<T>::get_default_cstr_count() {
    return default_cstr_count_;
}

template <typename T>
std::uint64_t SMF_call_counter<T>::get_misc_cstr_count() {
    return misc_cstr_count_;
}

template <typename T>
std::uint64_t SMF_call_counter<T>::get_copy_cstr_count() {
    return copy_cstr_count_;
}

template <typename T>
std::uint64_t SMF_call_counter<T>::get_move_cstr_count() {
    return move_cstr_count_;
}

template <typename T>
std::uint64_t SMF_call_counter<T>::get_copy_assignment_count() {
    return copy_assignment_count_;
}

template <typename T>
std::uint64_t SMF_call_counter<T>::get_move_assignment_count() {
    return move_assignment_count_;
}

template <typename T>
std::uint64_t SMF_call_counter<T>::get_destructor_count() {
    return destructor_count_;
}

template <typename T>
void SMF_call_counter<T>::reset_counts() {
    reset_default_cstr_count();
    reset_misc_cstr_count();
    reset_copy_cstr_count();
    reset_move_cstr_count();
    reset_copy_assignment_count();
    reset_move_assignment_count();
    reset_destructor_count();
}

template <typename T>
void SMF_call_counter<T>::reset_default_cstr_count() {
    default_cstr_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_misc_cstr_count() {
    misc_cstr_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_copy_cstr_count() {
    copy_cstr_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_move_cstr_count() {
    move_cstr_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_copy_assignment_count() {
    copy_assignment_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_move_assignment_count() {
    move_assignment_count_ = 0;
}

template <typename T>
void SMF_call_counter<T>::reset_destructor_count() {
    destructor_count_ = 0;
}

}  // namespace utility
