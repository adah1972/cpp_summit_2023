#include <chrono>
#include <iomanip>
#include <iostream>
#include <time.h>

using namespace std::chrono;
using std::cout;
using std::put_time;

int main()
{
    cout << "sizeof(nanoseconds) is " << sizeof(nanoseconds) << '\n';
    cout << "sizeof(seconds) is " << sizeof(seconds) << '\n';
    cout << "sizeof(hours) is " << sizeof(hours) << '\n';

    seconds s{1};
    milliseconds ms = s;

    ms = milliseconds{1500};
    // s = ms;
    s = duration_cast<seconds>(ms);
    duration<double> fs = ms;
    // ms = fs;

    cout << fs.count() << "s\n";

    time_point<system_clock, seconds> now{1702792800s};
    now -= 24h;
    now += 15h + 25min - 14h;
    time_t t = now.time_since_epoch().count();
    cout << put_time(localtime(&t), "%F %T") << '\n';

    static_assert(1h * 10 == 10h);
    static_assert(1h / 1min == 60);
}
