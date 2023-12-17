#include <chrono>
#include <iostream>

using namespace std::chrono;
using std::cout;

int main()
{
    for (auto yr = 2021y; yr != 2025y; ++yr) {
        auto mothers_day = yr / May / Sunday[2];
        cout << local_days{mothers_day} << '\n';
    }
}
