#include <iostream>
#include "5/Maze/AlterMazeState.h"
#include "5/playGame/play.h"
#include "5/playGame/minimax.h"
#include "5/playGame/montecarlo.h"
#include "5/playGame/thunder.h"
int main() {
    using std::cout;
    using std::endl;
    auto ais = std::array<StringAIPair, 2>{
        StringAIPair("mcts", [](const State& state){return mcts::mctsAction(state, 300);}),
        StringAIPair("thunder", [](const State& state){return thunder::thunderSearchAction(state, 100);})
    };
    testFirstPlayerWinRate(ais, 100);
    return 0;
}
