#include <chrono>
#include <iostream>

using namespace std::chrono;
using std::cout;

int main()
{
    auto dst_start_day = 2023y / March / Sunday[2];
    auto local_tp = local_days{dst_start_day} + 1h + 59min + 59s;
    auto* pst_tz = get_tzdb().locate_zone("US/Pacific");
    sys_time<milliseconds> sys_tp = pst_tz->to_sys(local_tp);
    for (int i = 0; i < 5; ++i) {
        auto zoned_tp = zoned_time{pst_tz, sys_tp};
        cout << zoned_tp << '\n';
        sys_tp += 500ms;
    }

    local_tp = local_days{dst_start_day} + 2h + 30min;
    try {
        cout << zoned_time(pst_tz, local_tp) << '\n';
    }
    catch (nonexistent_local_time& e) {
        cout << "*** Error:\n" << e.what() << '\n';
    }
}
