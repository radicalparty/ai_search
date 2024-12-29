#ifndef GREEDYSEARCH_H
#define GREEDYSEARCH_H

#include "../Maze/MazeState.h"
using State = MazeState;
class GreedySearch{
public:
    GreedySearch();
    int greedyAction(const State& state);
    void GreedyPlayGame(const int seed);
};

#endif