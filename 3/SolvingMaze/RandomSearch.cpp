#include <iostream>
#include "../Maze/MazeState.h"
#include "RandomSearch.h"

RandomSearch::RandomSearch(){mt_for_action = std::mt19937(0);}
//randomly select an action
int RandomSearch::randomAction(const State& state){
    auto actions = state.legalActions();
    return actions[mt_for_action() % actions.size()];
}

void RandomSearch::RandomPlayGame(const int seed){
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