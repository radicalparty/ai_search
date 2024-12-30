//
// Created by 88 88 on 24. 12. 29.
//

#ifndef AI_SEARCH_BEAMSEARCHWITHTIMEKEEPER_H
#define AI_SEARCH_BEAMSEARCHWITHTIMEKEEPER_H

#include "../Maze/MazeState.h"
#include "TimeKeeper.h"

using State = MazeState;

int beamSearchWithTimeThreshold(const State& state, const int beam_width, const int64_t time_threshold);

#endif //AI_SEARCH_BEAMSEARCHWITHTIMEKEEPER_H
