#ifndef AI_SEARCH_TIMEKEEPER_H
#define AI_SEARCH_TIMEKEEPER_H

#include <chrono> //the class manage the time in C++

class TimeKeeper {
private:
    std::chrono::high_resolution_clock::time_point start_time_;
    int64_t time_threshold_;
public:
    //setting the milliseconds as unit time
    TimeKeeper(const int64_t &time_threshold);

    //check whether time passed in duration since instance creation
    bool isTimeOver() const;
};


#endif //AI_SEARCH_TIMEKEEPER_H
