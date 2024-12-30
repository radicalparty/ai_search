#include "TimeKeeper.h"
#include <iostream>

//Why we use time keeper at beam search?
//because In large case, computer have to calculate problem fastly, so limited search is necessary

TimeKeeper::TimeKeeper(const int64_t &time_threshold): start_time_(std::chrono::high_resolution_clock::now()),
                                           time_threshold_(time_threshold) {}

bool TimeKeeper::isTimeOver() const{
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;

    bool rt = duration_cast<milliseconds>(diff).count() >= time_threshold_;
    if (rt) {
        std::cout << "Break!!" << std::endl;
    }
    return rt;
}