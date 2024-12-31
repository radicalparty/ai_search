#ifndef AI_SEARCH_PLAYGAME_H
#define AI_SEARCH_PLAYGAME_H

#include "../Maze/AutoMoveMazeState.h"
#include <iostream>

using State = AutoMoveMazeState;

using AIFunction = std::function<State(const State &)>;
using StringAIPair = std::pair<std::string, AIFunction>;

void playGame(const StringAIPair &ai, int seed);

#endif //AI_SEARCH_PLAYGAME_H
