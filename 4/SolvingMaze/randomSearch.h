#ifndef AI_SEARCH_RANDOMSEARCH_H
#define AI_SEARCH_RANDOMSEARCH_H

#include "../Maze/AutoMoveMazeState.h"
#include <functional>

using State = AutoMoveMazeState;
using AIFunction = std::function<State(const State &)>;
using StringAIPair = std::pair<std::string, AIFunction>;

State randomAction(const State& state);

#endif //AI_SEARCH_RANDOMSEARCH_H
