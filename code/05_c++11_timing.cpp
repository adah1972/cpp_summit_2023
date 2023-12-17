#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <ostream>
#include <ratio>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::chrono;

// Type trait to detect whether an output function already exists
template <typename T>
struct has_output_function {
    template <class U>
    static auto output(U* ptr)
        -> decltype(std::declval<std::ostream&>() << *ptr,
                    std::true_type());
    template <class U>
    static std::false_type output(...);
    static constexpr bool value =
        decltype(output<T>(nullptr))::value;
};
template <typename T>
inline constexpr bool has_output_function_v = has_output_function<T>::value;

// Adapted from P2080
template <typename T, template <typename...> class Primary>
struct is_specialization_of : std::false_type {};
template <template <typename...> class Primary, typename... Args>
struct is_specialization_of<Primary<Args...>, Primary> : std::true_type {};
template <typename T, template <typename...> class Primary>
inline constexpr bool is_specialization_of_v =
    is_specialization_of<T, Primary>::value;

// Hack for pre-C++20 compilers.  Not for production use!
template <typename Duration,
          std::enable_if_t<(!has_output_function_v<Duration> &&
                            is_specialization_of_v<Duration, duration>),
                           int> = 0>
std::ostream& operator<<(std::ostream& os, Duration dur)
{
    using period = typename Duration::period;
    const char* prefix{};
    if constexpr (std::is_same_v<period, std::nano>) {
        prefix = "n";
    } else if constexpr (std::is_same_v<period, std::micro>) {
        prefix = "u";
    } else {
        static const std::string prefix_content = [] {
            std::string result{"["};
            result += std::to_string(period::num);
            if constexpr (period::den != 1) {
                result += "/";
                result += std::to_string(period::den);
            }
            result += "]";
            return result;
        }();
        prefix = prefix_content.c_str();
    }
    os << dur.count() << prefix << "s";
    return os;
}

// Code below is addapted from
//     <URL:https://en.cppreference.com/w/cpp/chrono/time_point>

void slow_motion()
{
    static std::array a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // Generate 12! permutations
    while (std::next_permutation(a.begin(), a.end())) {
    }
}

int main()
{
    const time_point<system_clock> now = system_clock::now();
    const time_point<steady_clock> start = steady_clock::now();

    std::cout << "system_clock: " << now.time_since_epoch() << "\n"
                 "steady_clock: " << start.time_since_epoch() << '\n';

    slow_motion();

    const auto end = steady_clock::now();
    std::cout << "Slow calculations took "
              << duration_cast<microseconds>(end - start) << " ≈ "
              << (end - start) / 1ms << "ms ≈ "
              << (end - start + 500ms) / 1s << "s.\n";
}
