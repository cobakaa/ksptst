#include "../include/Timer.h"

void Timer::Start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::Finish() {
    finish_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish_time - start_time);
    t = duration;
    hours = std::chrono::duration_cast<std::chrono::hours>(t);
    t -= hours;
    mins = std::chrono::duration_cast<std::chrono::minutes>(t);
    t -= mins;
    secs = std::chrono::duration_cast<std::chrono::seconds>(t);
    t -= secs;
}