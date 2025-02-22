#include "../Maze/AlterMazeState.h"
#ifndef AI_SEARCH_MONTECARLO_H
#define AI_SEARCH_MONTECARLO_H

using State = AlterMazeState;
using ScoreType = int64_t;

constexpr const double C = 1;
constexpr const int EXPAND_THRESHOLD = 10;

namespace montecarlo{
    double playout(State* state);
    int primitiveMontecarloAction(const State& state, int playout_number);
}

namespace mcts{
    class Node {
    private:
        State state_;
        double w_;
    public:
        std::vector<Node> child_nodes_;
        double n_;
        Node(const State &state): state_(state), w_(0), n_(0) {};
        double evaluate();
        void expand();
        Node &nextChildNode();
    };
    int mctsAction(const State &state, const int playout_number);
}
#endif //AI_SEARCH_MONTECARLO_H
