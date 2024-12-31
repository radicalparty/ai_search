#include "randomSearch.h"
#include <random>
#include <iostream>

State randomAction(const State& state){
    State now_state = state;
    std::mt19937 mt_for_action(state.seed);
    for (int character_id = 0; character_id < state.character_num; character_id++){
        int y = abs((int)mt_for_action()) % state.H;
        int x = abs((int)mt_for_action()) % state.W;
        now_state.setCharacter(character_id, y, x);
    }

    return now_state;
}