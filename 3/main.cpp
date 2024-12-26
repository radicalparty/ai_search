#include "SolvingMaze/RandomSearch.h"
#include "SolvingMaze/GreedySearch.h"
int main(){
    RandomSearch random_search;
    GreedySearch greedy_search;
    random_search.RandomPlayGame(0);
    greedy_search.GreedyPlayGame(0);
    return 0;
}
