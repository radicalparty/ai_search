//
// Created by 88 88 on 24. 12. 30.
//

#ifndef AI_SEARCH_CHOKUDAI_H
#define AI_SEARCH_CHOKUDAI_H

#include "../Maze/MazeState.h"

using State = MazeState;

int chokudaiSearchAction(const State& state, const int beam_width, const int beam_depth, const int beam_number);


#endif //AI_SEARCH_CHOKUDAI_H
