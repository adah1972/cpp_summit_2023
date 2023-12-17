#include <chrono>
#include <format>
#include <iostream>

using namespace std::chrono;
using std::cout;
using std::format;

int main()
{
    auto sys_now = floor<milliseconds>(system_clock::now());
    auto utc_now = floor<milliseconds>(utc_clock::now());
    auto gps_now = floor<milliseconds>(gps_clock::now());
    auto tai_now = floor<milliseconds>(tai_clock::now());

    cout << format("Sys clock: {:%F %T %Z}", sys_now) << '\n';
    cout << format("UTC clock: {:%F %T %Z}", utc_now) << '\n';
    cout << format("GPS clock: {:%F %T %Z}", gps_now) << '\n';
    cout << format("TAI clock: {:%F %T %Z}", tai_now) << '\n';

    cout << '\n';
    auto sys_tp = sys_seconds{sys_days{1972y/7/1}};
    auto utc_tp = utc_clock::from_sys(sys_tp - 1s);
    cout << utc_tp << " UTC  ";
    cout << clock_cast<system_clock>(utc_tp) << " SYS  ";
    cout << clock_cast<tai_clock>(utc_tp) << " TAI\n";
    ++utc_tp;
    cout << utc_tp << " UTC  ";
    cout << clock_cast<system_clock>(utc_tp) << " SYS  ";
    cout << clock_cast<tai_clock>(utc_tp) << " TAI\n";
    ++utc_tp;
    cout << utc_tp << " UTC  ";
    cout << clock_cast<system_clock>(utc_tp) << " SYS  ";
    cout << clock_cast<tai_clock>(utc_tp) << " TAI\n";
}
