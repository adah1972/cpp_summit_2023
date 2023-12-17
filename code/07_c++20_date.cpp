#include <chrono>
#include <iostream>
#include <type_traits>

using namespace std::chrono;
using std::cout;
using std::decay_t;
using std::is_same_v;

int main()
{
    cout << 2023y/12/17 << '\n';
    cout << 12/17d/2023 << '\n';
    cout << 17d/12/2023 << '\n';
    cout << 17d/December/2023 << '\n';
    cout << December/17/2023 << '\n';
    cout << 2023y/December/17 << '\n';
    static_assert(is_same_v<decltype(2023y/12/17), year_month_day>);
    static_assert(is_same_v<decltype(December/17), month_day>);

    auto day31 = 2024y/1/31;
    cout << day31 + months{1} << '\n';
    cout << day31 + months{2} << '\n';

    auto day_last = 2024y/1/last;
    cout << day_last << ' ' << sys_days{day_last} << '\n';
    day_last += months{1};
    cout << day_last << ' ' << sys_days{day_last} << '\n';

    auto tp = sys_seconds{sys_days{day_last}};
    tp += months{1};
    cout << tp << '\n';
}
