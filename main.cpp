#include <iostream>
#include "5/Maze/AlterMazeState.h"
#include "5/playGame/play.h"
#include "5/playGame/minimax.h"
int main() {
    using std::cout;
    using std::endl;
    auto ais = std::array<StringAIPair, 2>{
        StringAIPair("miniMaxAction", [](const State& state){return minimax::miniMaxAction(state, END_TURN);}),
        StringAIPair("randomAction", [](const State& state){return randomAction(state);})
    };
    testFirstPlayerWinRate(ais, 100);
    return 0;
}
