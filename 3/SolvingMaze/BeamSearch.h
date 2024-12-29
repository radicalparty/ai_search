#ifndef AI_SEARCH_BEAMSEARCH_H
#define AI_SEARCH_BEAMSEARCH_H
#include "../Maze/MazeState.h"
using State = MazeState;

int beamSearchAction(const State &state, const int beam_width, const int beam_depth);

#endif //AI_SEARCH_BEAMSEARCH_H
