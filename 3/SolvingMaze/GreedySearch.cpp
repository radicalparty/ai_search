#include "../Maze/MazeState.h"
#include "GreedySearch.h"
#include <iostream>
using State = MazeState;

GreedySearch::GreedySearch(){}
int GreedySearch::greedyAction(const State& state){
    auto legal_actions = state.legalActions();
    int64_t max_score = -1e9;
    int best_action = -1;
    for (const auto action : legal_actions){
        State next_state = state;
        next_state.advance(action);
        if (next_state.game_score_ > max_score){
            max_score = next_state.game_score_;
            best_action = action;
        }
    }
    return best_action;
}

void GreedySearch::GreedyPlayGame(const int seed){
    State state(3, 4, 4, seed);
    std::cout << "Greedy Action" << "\n";
    while(!state.isDone()){
        std::cout << "-----------------" << "\n";
        state.advance(greedyAction(state));
        std::cout << state.toString() << std::endl;
    }
    std::cout << "Game score: " << state.game_score_ << std::endl;
    std::cout << "---------------------" << "\n";
    return;
}