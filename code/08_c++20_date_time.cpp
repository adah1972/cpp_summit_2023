#include <chrono>
#include <format>
#include <iostream>
#include <type_traits>

using namespace std::chrono;
using std::cout;
using std::format;
using std::is_same_v;

int main()
{
    auto sys_tp = sys_days{2023y/12/17} + 14h + 25min;
    static_assert(is_same_v<decltype(sys_tp), sys_time<minutes>>);
    cout << sys_tp << '\n';

    cout << format("{}", sys_tp) << '\n';
    cout << format("{:%F %T}", sys_tp) << '\n';
    cout << format("{:%d-%b-%Y %H:%M}", sys_tp) << '\n';
    cout << format("{:%F %T %Z}", sys_tp) << '\n';

    auto local_tp = local_days{2023y/12/17} + 14h + 25min;
    cout << local_tp << '\n';

    auto* local_tz = get_tzdb().current_zone();
    auto zoned_tp = zoned_time{local_tz, local_tp};
    cout << zoned_tp << '\n';

    cout << sizeof local_tp << '\n';
    cout << sizeof zoned_tp << '\n';

    auto* pst_tz = get_tzdb().locate_zone("US/Pacific");
    auto pst_tp = zoned_time{pst_tz, zoned_tp};
    cout << pst_tp << '\n';

    auto now = system_clock::now();
    cout << "UTC today:   " << floor<days>(now) << '\n';
    auto local_now = local_tz->to_local(now);
    cout << "Local today: " << floor<days>(local_now) << '\n';
    auto pst_now = pst_tz->to_local(now);
    cout << "PST today:   " << floor<days>(pst_now) << '\n';
}
