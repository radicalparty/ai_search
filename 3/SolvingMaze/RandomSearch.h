#ifndef RANDOMSEARCH_H
#define RANDOMSEARCH_H
#include "../Maze/MazeState.h"
using State = MazeState;
class RandomSearch{
private:
    std::mt19937 mt_for_action;
public:
    RandomSearch();
    int randomAction(const State& state);
    void RandomPlayGame(const int seed);
};
#endif