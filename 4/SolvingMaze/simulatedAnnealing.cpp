#include "simulatedAnnealing.h"
#include <random>
#define INF 1'000'000'000

State simulatedAnnealing(const State& state, int number, double start_temp, double end_temp){
    State now_state = state;
    std::mt19937 mt_for_action(state.seed);
    now_state.init();
    int64_t best_score = now_state.getScore();
    int64_t now_score = best_score;
    auto best_state = now_state;

    for (int i = 0; i < number; i++){
        auto next_state = now_state;
        next_state.transition();

        auto next_score = next_state.getScore();
        double temp = start_temp + (end_temp - start_temp) * ((double)i / number);
        double prob = exp((double)(next_score - now_score) / temp);

        bool is_force_next = prob > (((int)mt_for_action() % INF) / (double)INF);

        if (next_score > now_score || is_force_next){
            now_state = next_state; now_score = next_score;
        }

        if (next_score > best_score){
            best_score = next_score;
            best_state = next_state;
        }
    }
    return best_state;
}