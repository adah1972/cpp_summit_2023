#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>

#if (__cplusplus >= 201703L ||                                             \
     (defined(_MSC_VER) && _MSC_VER >= 1910 && _MSVC_LANG >= 201703L)) &&  \
    __has_include(<mozi/print.hpp>)
#define HAVE_MOZI 1
#include <mozi/print.hpp>
#include <mozi/struct_reflection.hpp>
#endif

#if !(defined(__unix__) || defined(__unix) ||                              \
      (defined(__APPLE__) && defined(__MACH__)))
#error "This example is for Unix systems only!"
#endif

#include <sys/time.h>

#if HAVE_MOZI
DEFINE_STRUCT(           //
    TimeVal,             //
    (time_t)tv_sec,      /* seconds */
    (suseconds_t)tv_usec /* and microseconds */
);
#endif

using std::cout;

int main()
{
    tm tm_data;
    memset(&tm_data, 0, sizeof tm_data);
    tm_data.tm_year = 2023 - 1900;
    tm_data.tm_mon = 12 - 1;
    tm_data.tm_mday = 17;
    tm_data.tm_hour = 14;
    time_t t = mktime(&tm_data);
    cout << t << '\n';

    char buffer[40];
    strftime(buffer, sizeof buffer, "%F %T %Z", &tm_data);
    puts(buffer);

    time(&t);
    localtime_r(&t, &tm_data);
    strftime(buffer, sizeof buffer, "%F %T %Z", &tm_data);
    puts(buffer);

    timeval tv;
    gettimeofday(&tv, nullptr);
#if HAVE_MOZI
    TimeVal tv_to_print{};
    memcpy(&tv_to_print, &tv,
           sizeof(TimeVal));
    mozi::println(tv_to_print);
#endif
    localtime_r(&tv.tv_sec, &tm_data);
    strftime(buffer, sizeof buffer, "%F %T", &tm_data);
    printf("%s.%06d\n", buffer, static_cast<int>(tv.tv_usec));

    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm_data);
    strftime(buffer, sizeof buffer, "%F %T", &tm_data);
    printf("%s.%09ld\n", buffer, ts.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &ts);
    printf("%ld.%09ld\n", static_cast<long>(ts.tv_sec), ts.tv_nsec);
}
