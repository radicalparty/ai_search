#ifndef AI_SEARCH_SIMULATEDANNEALING_H
#define AI_SEARCH_SIMULATEDANNEALING_H
#include "../Maze/AutoMoveMazeState.h"
using State = AutoMoveMazeState;

State simulatedAnnealing(const State& state, int number, double start_temp, double end_temp);

#endif //AI_SEARCH_SIMULATEDANNEALING_H
