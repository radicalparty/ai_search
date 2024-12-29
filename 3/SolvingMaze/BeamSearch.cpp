#include "../Maze/MazeState.h"
using State = MazeState;
int beamSearchAction(const State& state, const int beam_width, const int beam_depth){
    std::priority_queue<State> now_beam;
    State best_state;
    now_beam.emplace(state);

    for (int t = 0; t < beam_depth; t++){
        std::priority_queue<State> next_beam;
        for (int i = 0; i < beam_width; i++){
            if (now_beam.empty()) break;
            State now_state = now_beam.top(); now_beam.pop();
            auto legal_actions = now_state.legalActions();
            for (const auto& action: legal_actions){
                State next_state = now_state;
                next_state.advance(action);
                next_state.evaluateScore();
                if (t == 0) next_state.first_action_ = action;
                next_beam.emplace(next_state);
            }
        }
        now_beam = next_beam;
        best_state = now_beam.top();

        if (best_state.isDone()) break;
    }
    return best_state.first_action_;
}