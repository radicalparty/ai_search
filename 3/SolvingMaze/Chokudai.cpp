#include "Chokudai.h"

int chokudaiSearchAction(const State& state, const int beam_width, const int beam_depth, const int beam_number){
    auto beam = std::vector<std::priority_queue<State>>(beam_depth + 1, std::priority_queue<State>());

    beam[0].emplace(state);

    for (int cnt = 0; cnt < beam_number; cnt++){
        for (int t = 0; t < beam_depth; t++){
            auto& now_beam = beam[t];
            auto& next_beam = beam[t + 1];

            for (int i = 0; i < beam_width; i++){
                if (now_beam.empty()){
                    break;
                }

                State now_state = now_beam.top();

                if (now_state.isDone()) break;

                now_beam.pop();

                auto legal_actions = now_state.legalActions();

                for (const auto& action: legal_actions){
                    State next_state = now_state;
                    next_state.advance(action);
                    next_state.evaluateScore();
                    if (t == 0){
                        next_state.first_action_ = action;
                    }
                    next_beam.emplace(next_state);
                }
            }
        }
    }

    for (int t = beam_depth; t >= 0; t--){
        const auto& now_beam = beam[t];

        if (!now_beam.empty()) return now_beam.top().first_action_;
    }

    return -1;
}
