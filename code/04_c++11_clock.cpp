#include <chrono>
#include <iostream>
#include <type_traits>

using namespace std::chrono;
using std::cout;

int main()
{
    static_assert(steady_clock::is_steady);
    static_assert(!system_clock::is_steady);
    static_assert(!std::is_same_v<system_clock, steady_clock>);
    if (std::is_same_v<high_resolution_clock, system_clock>) {
        cout << "high_resolution_clock is system_clock\n";
    } else if (std::is_same_v<high_resolution_clock, steady_clock>) {
        cout << "high_resolution_clock is steady_clock\n";
    } else {
        cout << "high_resolution_clock is not an alias\n";
    }
}
