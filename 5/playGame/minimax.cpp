#include "minimax.h"
#define INF 1e9

ScoreType minimax::miniMaxScore(const State &state, const int depth) {
    if (state.isDone() || depth == 0){
        return state.getScore();
    }
    auto legal_actions = state.legalActions();
    if (legal_actions.empty()) return state.getScore();
    ScoreType bestScore = -INF;
    for (const auto action: legal_actions){
        State next_state = state;
        next_state.advance(action);
        ScoreType score = -miniMaxScore(next_state, depth - 1);
        if (score > bestScore) bestScore = score;
    }
    return bestScore;
}

int minimax::miniMaxAction(const State &state, const int depth) {
    ScoreType best_action = -1;
    ScoreType best_score = -INF;
    for (const auto action: state.legalActions()){
        State next_state = state;
        next_state.advance(action);
        ScoreType score = -miniMaxScore(next_state, depth);
        if (score > best_score){
            best_action = action;
            best_score = score;
        }
    }
    return best_action;
}

using minimax::miniMaxAction;