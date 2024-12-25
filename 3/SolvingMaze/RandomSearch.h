#ifndef RANDOMSEARCH_H
#define RANDOMSEARCH_H
#include "../Maze/MazeState.h"
using State = MazeState;
int randomAction(const State& state);
void RandomPlayGame(const int seed);

#endif // RANDOMSEARCH_H