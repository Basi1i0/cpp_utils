#ifndef  TIME_UTILS_H
#define TIME_UTILS_H

#include <chrono>

inline auto get_interval(std::chrono::steady_clock::time_point& start)
{
    auto current{ std::chrono::high_resolution_clock::now() };
    auto interval = current - start;
    start = current;
    return interval;
}

#endif // ! TIME_UTILS_H