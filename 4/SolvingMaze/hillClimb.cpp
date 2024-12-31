#include "hillClimb.h"

State hillClimb(const State& state, int number){
    State now_state = state;
    now_state.init();
    int64_t best_score = now_state.getScore();

    for (int i = 0; i < number; i++){
        auto next_state = now_state;
        next_state.transition();
        auto next_score = next_state.getScore();
        if (next_score > best_score){
            best_score = next_score;
            now_state = next_state;
        }
    }

    return now_state;
}