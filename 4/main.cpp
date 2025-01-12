#include <iostream>
#include "SolvingMaze/randomSearch.h"
#include "SolvingMaze/hillClimb.h"
#include "SolvingMaze/simulatedAnnealing.h"
#include "SolvingMaze/playGame.h"
#include "Maze/AutoMoveMazeState.h"

using AIFunction = std::function<State(const State &)>;
using StringAIPair = std::pair<std::string, AIFunction>;

int main() {
    int x; std::cin >> x;
    const auto &ai1 = StringAIPair("randomAction", [&](const State& state){return randomAction(state);});
    const auto& ai2 = StringAIPair("hillClimb", [&](const State& state){return hillClimb(state, 1);});
    const auto& ai3 = StringAIPair("simulatedAnnealing", [&](const State& state){return simulatedAnnealing(state, 1, 500, 10);});
    playGame(ai1, x);
    playGame(ai2, x);
    playGame(ai3, x);
    return 0;
}