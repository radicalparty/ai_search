#include <iostream>
#include "../Maze/MazeState.h"
#include "RandomSearch.h"

std::mt19937 mt_for_action(0);
//randomly select an action
int randomAction(const State& state){
    auto actions = state.legalActions();
    return actions[mt_for_action() % actions.size()];
}

void RandomPlayGame(const int seed){
    State state(3, 4, 4, seed);
    std::cout << "Random Action" << "\n";
    while(!state.isDone()){
        std::cout << "-----------------" << "\n";
        state.advance(randomAction(state));
        std::cout << state.toString() << std::endl;
    }
    std::cout << "Game score: " << state.game_score_ << std::endl;
    std::cout << "---------------------" << "\n";
    return;
}