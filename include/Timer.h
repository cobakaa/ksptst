
#ifndef KSPTST_TIMER_H
#define KSPTST_TIMER_H
#include <chrono>


class Timer {
public:
    void Start();
    void Finish();

    std::chrono::hours hours;
    std::chrono::minutes mins;
    std::chrono::seconds secs;
    std::chrono::milliseconds t;

private:
    std::chrono::duration<long int, std::milli> duration;
    std::chrono::high_resolution_clock::time_point start_time, finish_time;
};


#endif //KSPTST_TIMER_H
