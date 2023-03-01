
#include "cross_platform_porting.h"
#include <iostream>
#include <chrono>
#include "measure_time.h"


extern "C" int measure(work_fn work, report_fn report, const char *title, void *closure) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int rv = work(title, closure);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    long long ms = time / std::chrono::nanoseconds(1);

    rv += report(ms / 1.0E6, title, closure);

    return rv;
}

