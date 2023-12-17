#include <chrono>
#include <iostream>

using namespace std::chrono;
using std::cout;

int main()
{
    auto* tz_ptr = get_tzdb().locate_zone("Asia/Shanghai");
    for (auto yr = 1980y; yr != 2000y; ++yr) {
        auto local_tp = local_days{yr / June / 1};
        auto sys_tp = sys_days{yr / June / 1};
        auto diff = sys_tp - tz_ptr->to_sys(local_tp);
        if (diff != 8h) {
            cout << yr << '\n';
        }
    }
}
