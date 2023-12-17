#include <chrono>
#include <iostream>
#include <thread>

namespace this_thread = std::this_thread;
using namespace std::chrono;
using std::cout;

int main()
{
    auto tp = system_clock::now();
    cout << tp << '\n';
    this_thread::sleep_for(100ms);
    cout << duration_cast<milliseconds>(system_clock::now() - tp) << '\n';
}
