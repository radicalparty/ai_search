#ifndef AI_SEARCH_PLAY_H
#define AI_SEARCH_PLAY_H
#include "../Maze/AlterMazeState.h"
#include <iostream>

using State = AlterMazeState;

int randomAction(const State& state);

void playGame(const int seed);


#endif //AI_SEARCH_PLAY_H