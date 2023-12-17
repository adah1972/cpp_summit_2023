#include <iostream>
#include <stdio.h>
#include <stdlib.h>  // IWYU pragma: keep setenv/_putenv
#include <string.h>
#include <time.h>

#if (__cplusplus >= 201703L ||                                             \
     (defined(_MSC_VER) && _MSC_VER >= 1910 && _MSVC_LANG >= 201703L)) &&  \
    __has_include(<mozi/print.hpp>)
#define HAVE_MOZI 1
#include <mozi/print.hpp>
#include <mozi/struct_reflection.hpp>
#endif

#if defined(__unix__) || defined(__unix) ||                                \
    (defined(__APPLE__) && defined(__MACH__))
#define UNIX 1
#elif !defined(_WIN32)
#error "Unknown platform"
#endif

#ifdef UNIX
#include <sys/time.h>

#if HAVE_MOZI
DEFINE_STRUCT(           //
    TimeVal,             //
    (time_t)tv_sec,      /* seconds */
    (suseconds_t)tv_usec /* and microseconds */
);
#endif
#endif

#if HAVE_MOZI
#if UNIX
DEFINE_STRUCT(       //
    Time,            //
    (int)tm_sec,     /* seconds after the minute [0-60] */
    (int)tm_min,     /* minutes after the hour [0-59] */
    (int)tm_hour,    /* hours since midnight [0-23] */
    (int)tm_mday,    /* day of the month [1-31] */
    (int)tm_mon,     /* months since January [0-11] */
    (int)tm_year,    /* years since 1900 */
    (int)tm_wday,    /* days since Sunday [0-6] */
    (int)tm_yday,    /* days since January 1 [0-365] */
    (int)tm_isdst,   /* Daylight Savings Time flag */
    (long)tm_gmtoff, /* offset from UTC in seconds */
    (char*)tm_zone   /* timezone abbreviation */
);
#elif defined(_WIN32)
DEFINE_STRUCT(       //
    Time,            //
    (int)tm_sec,     /* seconds after the minute [0-60] */
    (int)tm_min,     /* minutes after the hour [0-59] */
    (int)tm_hour,    /* hours since midnight [0-23] */
    (int)tm_mday,    /* day of the month [1-31] */
    (int)tm_mon,     /* months since January [0-11] */
    (int)tm_year,    /* years since 1900 */
    (int)tm_wday,    /* days since Sunday [0-6] */
    (int)tm_yday,    /* days since January 1 [0-365] */
    (int)tm_isdst    /* Daylight Savings Time flag */
);
#endif
#endif

using std::cout;

int main()
{
    time_t t = 0;
    cout << ctime(&t);
    tm* tm_ptr = gmtime(&t);
    cout << asctime(tm_ptr);  // NOLINT(bugprone-unsafe-functions)

#if HAVE_MOZI
    Time time_to_print{};
    memcpy(&time_to_print, tm_ptr, sizeof(Time));
    mozi::println(time_to_print);
    static_assert(sizeof *tm_ptr == sizeof time_to_print);
    memcpy(&time_to_print, localtime(&t), sizeof(Time));
    mozi::println(time_to_print);
#endif

#if UNIX
    setenv("TZ", ":US/Pacific", 1);
    tzset();
#else
    _putenv("TZ=PST8PDT");
    _tzset();
#endif
    tm_ptr = localtime(&t);
#if HAVE_MOZI
    memcpy(&time_to_print, localtime(&t), sizeof(Time));
    mozi::println(time_to_print);
#endif
    cout << asctime(tm_ptr);  // NOLINT

#if UNIX
    setenv("TZ", ":UTC", 1);
    tzset();
    tm tm_data;
    localtime_r(&t, &tm_data);
    char buffer[40];
    strftime(buffer, sizeof buffer, "%F %T %Z", &tm_data);
    puts(buffer);
#endif

#if UNIX
    unsetenv("TZ");
    tzset();
#else
    _putenv("TZ=");
    _tzset();
#endif
}
