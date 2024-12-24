#include <iostream>
#include "../Maze/MazeState.cpp"
std::mt19937 mt_for_action(0);
using State = MazeState;
//randomly select an action
int randomAction(const State& state){
    auto actions = state.legalActions();
    return actions[mt_for_action() % actions.size()];
}

void playGame(const int seed){
    State state(3, 4, 4, seed);
    std::cout << "-----------------" << "\n";
    while(!state.isDone()){
        state.advance(randomAction(state));
        std::cout << state.toString() << std::endl;
    }
    std::cout << "Game score: " << state.game_score_ << std::endl;
    return;
}