#include "../Maze/AlterMazeState.h"
#ifndef AI_SEARCH_MINIMAX_H
#define AI_SEARCH_MINIMAX_H

using State = AlterMazeState;
using ScoreType = int64_t;

namespace minimax{
    ScoreType miniMaxScore(const State& state, const int depth);
    int miniMaxAction(const State& state, const int depth);
}

namespace alphabeta{
    //alpha: 현재 차례 플레이어의 최고 점수 -> 점수가 alpha보다 클 때 갱신
    //beta: 다른 플레이어의 최고 점수 -> 점수가 beta보다 커지면 alpha를 돌려주고 탐색을 종료
    ScoreType alphaBetaScore(const State& state, ScoreType alpha, const ScoreType beta, const int depth);
    int alphaBetaAction(const State& state, const int depth);
}


#endif //AI_SEARCH_MINIMAX_H
