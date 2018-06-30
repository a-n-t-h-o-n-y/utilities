# Scripts
### cppinit.py
Initialized a directory with `CMakeLists.txt`, `main.cpp`, `test.cpp` and a
`build` folder.

### mkclass.py
Creates a header and source file for a class name argument. Create a template
with `-t [Parameter Names...]`.

### install.py
Installs all scripts to `/usr/local/bin/` unless alternative path is provided as
an argument, scripts are installed as executable and without any extension.
Installs all headers in `/usr/local/include/utility/`.

# C++ Headers
### unsigned_integer.hpp
Big Integer class template with compile time bit precision. Implements:
- operator+
- operator-
- operator\*
- operator/
- operator%
- exp()
- root()
- Comparison, Bitwise, Increment/Decrement and Compound Assignment operators
- Copy/Assignment from integer literals, std::bitset, Unsigned_integers of any
  precision, std::string and const char\* interpreted as a Decimal value, unless
  a prefix is used ('0x' - Hexadecimal, '0' - Octal, '0b' - Binary)
```cpp
#include <utility/unsigned_integer.hpp>

template <std::size_t N>
using uInt = utility::Unsigned_integer<N>;

int main() {
    assert(uInt<256>::precision == 256);
    assert(uInt<5000>::precision == 5000);

    uInt<128> i_128{"340282366920938463463374607431768211455"};  // Dec
    uInt<4> i_4{12};

    assert((i_128 / i_4).precision == 128);
    assert((i_4 / i_128).precision == 4);
    assert((i_128 = i_4) == 12);

    i_128 = std::bitset<128>{"10010101"};
    assert(i_128.to_string(16) == "95");  // ::to_string(int base)
    assert(i_128.to_string(8) == "225");
    assert(i_128.to_string(3) == "12112");
    assert(i_128.to_string(20) == "79");
    assert(i_128.to_string() == "149");

    i_128 = "0x2da4a5515";  // Hex
    assert(i_128.to_string(2) == "1011011010010010100101010100010101");

    i_128 = "01234567";  // Octal
    assert(i_128.to_string() == "342391");
}
```

### property.hpp
Wraps a value and provides get/set members. Setting the value emits a Signal
which passes on the value set.
```cpp
#include <utility/property.hpp>
int main() {
    int flag{0};
    utility::Property<int> i{5};
    i.on_change().connect([&flag](int x) { flag = x; });
    i.set(17);
    assert(flag == 17);
}
```

### log.hpp
Simple Logging class, can log to any stream with `Basic_log<Stream_t>` class
template. Provides convenience objects log_cout, log_cerr, and log_clog, as well
as Log type alias to stream to an ofstream.
```cpp
#include <utility/log.hpp>

using namespace std::chrono_literals;
int main() {
    utility::Log log;  // Defaults to file named log.txt, appends text
    log << "Hello, log" << std::endl;
    log.set_width(16);  // minimum width for label in Log::value()
    log.value("Magic Number", 18);
    log.timestamp();
    log.line_break();

    utility::log_cout.start_timer();
    std::this_thread::sleep_for(2s);
    utility::log_cout.end_timer();
    utility::log_cout.output_timer<std::chrono::milliseconds>();
}
```

### cout_new.hpp, cerr_new.hpp, clog_new.hpp
Operator new overloads, displaying each allocation's size and location.
Deallocations provide the location. Only include one of these headers, and all
allocations made within the translation unit will be recorded. Totals are given
at the end of program execution. Also possible to provide your own stream by
defining a std::ostream object named `utility::detail::stream_` as shown below.
```cpp
namespace utility {
namespace detail {

std::ostream& stream_{my_stream};

}  // namespace detail
}  // namespace utility

#include <utility/detail/new_overloads.hpp>
```

### type_view.hpp
Output type traits and numeric limits to a given stream.
```cpp
#include <utility/type_view.hpp>
int main() {
    utility::type_view::primary_categories<int>();  // (os = std::cout)
    utility::type_view::composite_categories<int>();
    utility::type_view::type_properties<int>();
    utility::type_view::operations<int, double>();  // <T, U = T>
    utility::type_view::property_queries<int>();
    utility::type_view::type_relationships<int, double>();  // <T, U = T>
    utility::type_view::limits<int>();

    utility::type_view_all<int, double>();  // <T, U = T>
}
```

### memory_view.hpp
Provides functions to output raw data representation of any object. Data types
larger than `size_of(unsigned long long)`, typically 64 bits, can only be
displayed as binary.
```cpp
#include <utility/memory_view.hpp>
int main() {
    const std::uint16_t i{255};

    // Memory View Object
    utility::Memory_view<std::uint16_t> int_view{i};
    assert(int_view.str() == "0000 0000 1111 1111");

    int_view.enable_seperators(false);  // Seperate into bytes, on by default.
    assert(int_view.str() == "0000000011111111");

    int_view.enable_seperators();
    int_view.set_representation(utility::Hex);  // Or Binary, Decimal, Octal
    assert(int_view.str() == "FF");

    // Convinience Functions
    char16_t c{0b0010000010101100};
    std::string binary{utility::as_binary(c)};  // (T obj, seperators = true)
    std::string octal{utility::as_octal(c)};    // Does not have seperators
    std::string hexadecimal{utility::as_hex(c, false)};
    std::string decimal{utility::as_decimal(c)};

    assert(binary == "0010 0000 1010 1100");
    assert(octal == "20254");
    assert(hexadecimal == "20AC");
    assert(decimal == "8,364");
}
```

### container_view.hpp
Formats a container of objects in a readable way, if the type has the
std::ostream insertion operator overloaded. Returns as a std::string.
```cpp
#include <utility/container_view.hpp>
int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::string vec_view{utility::container_view(vec)};
    assert(vec_view == "{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }");

    // Using iterators
    vec_view = utility::container_view(std::begin(vec), std::begin(vec) + 3);
    assert(vec_view == "{ 1, 2, 3 }");
}
```

### trait_conjunction.hpp
Type trait to check a trait against multiple types, providing a static `value`
member if each type is true to the trait.
```cpp
#include <utility/trait_conjunction.hpp>
struct Foo {};
struct Bar {};

template <typename... Types>
constexpr bool is_class() {
    return utility::trait_conjunction_v<std::is_class, Types...>;
}

int main() {
    using TC_1 = utility::Trait_conjunction<std::is_class, Foo, Bar>;
    assert(TC_1::value);    

    using TC_2 = utility::Trait_conjunction<std::is_class, int, double, Foo>;
    assert(!TC_2::value);

    constexpr bool var =
        utility::trait_conjunction_v<std::is_void, void, void, void, void>;
    assert(var);

    constexpr bool var_3 = is_class<Foo, Bar>();
    assert(var_3);

    constexpr bool var_4 = is_class<Foo, Bar, int, double, Foo, int>();
    assert(!var_4);
}
```

### type_info.hpp
Provides unmangled names as well as cv-qualified and reference type infomation
for a provided type.
```cpp
#include <utility/type_info.hpp>
int main() {
    utility::Type_info info_1 = utility::get_type_info<int>();
    assert("int" == static_cast<std::string>(info_1));

    utility::Type_info info_2{utility::get_type_info<const volatile int&&>()};
    assert("const volatile int&&" == info_2.full_type_name());
    assert("int" == info_2.type_name());
    
    utility::Type_info info_3{
        utility::get_type_info<volatile long** const*** volatile* const>()};
    assert("long volatile** const*** volatile* const" == 
              info_3.full_type_name());

    // Function Types
    using Func1_t = Foo (*)(int, long);
    utility::Type_info info_4{utility::get_type_info<Func2_t>()};
    assert("Foo (*)(int, long)" == info_4.full_type_name());

    using Func2_t = int (*volatile &&)(int);
    using Func3_t = Func2_t (*const volatile&&)(Func2_t);
    utility::Type_info info_5{utility::get_type_info<Func7_t>()};
    assert(
        "int (* volatile&& (* const volatile&&)(Foo (*)(int, long)))(int)" ==
        info_5.full_type_name());
}
```

### smf_call_counter.hpp
Template wrapper providing counts of the number of times each Special Member
Function has been called.
```cpp
#include <utility/smf_call_counter.hpp>
int main() {
    // Built-ins
    using Integer = utility::SMF_call_counter<int>;
    {
        Integer var_1;        // Default Constructor
        Integer var_2{1};     // Copy Constructor
        var_1 = var_2;        // Copy Assignment
        var_2 = 42;           // Copy Assignment
    }
    assert(1 == Integer::get_default_cstr_count());
    assert(1 == Integer::get_copy_cstr_count());
    assert(2 == Integer::get_copy_assignment_count());
    assert(2 == Integer::get_destructor_count());

    Integer::all_counts_as_string();
    Integer::copy_cstr_as_string();
    Integer::reset_copy_assignment_count();
    Integer::reset_counts();

    // Non-Trivial Classes
    using Unique_ptr = utility::SMF_call_counter<std::unique_ptr<int>>;
    {
        Unique_ptr var_1;                            // Default constructor
        Unique_ptr var_2{std::make_unique<int>(1)};  // Move constructor
        Unique_ptr var_3{std::move(var_2)};          // Move constructor
        var_1 = std::move(var_3);                    // Move assignment
        var_1.reset()     // Transparent calls to template type's members.
    }
    assert(1 == Unique_ptr::get_default_cstr_count());
    assert(0 == Unique_ptr::get_direct_cstr_counts());
    assert(0 == Unique_ptr::get_direct_cstr_count<std::unique_ptr<int>>());
    assert(0 == Unique_ptr::get_copy_cstr_count());
    assert(2 == Unique_ptr::get_move_cstr_count());
    assert(0 == Unique_ptr::get_assignment_counts());
    assert(0 == Unique_ptr::get_copy_assignment_count());
    assert(1 == Unique_ptr::get_move_assignment_count());
    assert(3 == Unique_ptr::get_destructor_count());

    // C-Arrays
    using Array = utility::SMF_call_counter<int[5]>;
    {
        Array var_1;                 // Default Constructor
        Array var_2{1, 2, 3, 4, 5};  // Initializer List Constructor
        Array var_3{1, 2, 3};        // Initializer List Constructor
        Array var_4{};               // Default Constructor
    }
    assert(2 == Array::get_default_cstr_count());
    assert(2 == Array::get_initializer_list_cstr_count());
    assert(4 == Array::get_destructor_count());

    // Aggregates
    struct Bar { int a; double b; char c; };
    using Baz = utility::SMF_call_counter<Bar>;
    {
        Baz var_1;                    // Default Constructor
        Baz var_2{1, 2.3, 'a'};       // Aggregate Direct Constructor
        Baz var_3{var_2};             // Copy Constructor
        Baz var_4{std::move(var_2)};  // Copy Constructor
        Baz var_5{Baz{3, 2.1, 'b'}};  // Aggregate Direct Cstr; Copy Elision
        var_1 = var_3;                // Copy Assignment
        var_3 = std::move(var_1);     // Copy Assignment
    }
    assert(1 == Baz::get_default_cstr_count());
    assert(2 == Baz::get_direct_cstr_counts());
    assert(2 == (Baz::get_direct_cstr_count<int, double, char>()));
    assert(2 == Baz::get_copy_cstr_count());
    assert(2 == Baz::get_copy_assignment_count());
    assert(5 == Baz::get_destructor_count());

    Array::direct_cstr_count_as_string<int, double, char>();
    Array::direct_cstr_counts_as_string();
    Array::reset_direct_cstr_count<int, double, char>();
    Array::reset_direct_cstr_counts();
}
```

### random_value.hpp
Produces individual random values as well as containers of values.
```cpp
#include <utility/random_value.hpp>
int main() {
    const int lower_bound{0};
    const int upper_bound{255};

    // Single random value
    int rand{utility::random_value<int>(lower_bound, upper_bound)};
    float rand_f{utility::random_value<float>(lower_bound, upper_bound)};

    // Container of values
    const std::size_t size{32};
    auto container = utility::random_values<std::vector<double>>(
        size, lower_bound, upper_bound);

    // Array type of values
    auto array =
        utility::random_values<std::array<int, size>>(lower_bound, upper_bound);
}
```

### thousands_seperator.hpp
Convinience function to add a seperator at every thousands place in a number.
```cpp
#include <utility/thousands_seperator.hpp>
int main() {
    const int value{123456789};
    std::string formatted_value{utility::thousands_seperator(value)};
    assert(formatted_value == "123,456,789");
}
```

### strong_guarantee.hpp
Provides the strong exception guarantee to any container member function by a
copy and swap. Specify the member function type to avoid ambiguity.
```cpp
#include <utility/strong_guarantee.hpp>
using Container = std::vector<int>;

// Member function type.
template <typename Ret, typename... Args>
using Mem_fn = Ret (Container::*)(Args...);

int main() {
    Container v{5, 4, 3, 2, 1};

    // Provide a member function, a Container, and the function's arguments.
    // (mem_fn, Container, Args...)
    utility::make_operation_strong(&Container::empty, v);

    // iter Container::insert(const_iter, const_iter) overloaded function
    using Insert_overload =
        Mem_fn<Container::iterator, Container::const_iterator,
               Container::const_reference>;

    // Explicit template parameter for functions with overloads.
    utility::make_operation_strong<Insert_overload>(&Container::insert, v,
                                                    std::begin(v), 6);
}
```

### narrow_cast.hpp
Throws a std::runtime_error if the cast will narrow the value and cause it to
loose precision.
```cpp
#include <utility/narrow_cast.hpp>
int main() {
    const std::int32_t source{2147483647};
    try {
        utility::narrow_cast<std::int16_t>(source);
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }
}
```

