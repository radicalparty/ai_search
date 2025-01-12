#include "../Maze/AlterMazeState.h"
#ifndef AI_SEARCH_MINIMAX_H
#define AI_SEARCH_MINIMAX_H

using State = AlterMazeState;
using ScoreType = int64_t;

namespace minimax{
    ScoreType miniMaxScore(const State& state, const int depth);
    int miniMaxAction(const State& state, const int depth);
}


#endif //AI_SEARCH_MINIMAX_H
