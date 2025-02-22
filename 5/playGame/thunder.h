#include "../Maze/AlterMazeState.h"
#ifndef AI_SEARCH_THUNDER_H
#define AI_SEARCH_THUNDER_H

namespace thunder{
    class Node{
    private:
        State state_;
        double w_;
    public:
        std::vector<Node> child_nodes_;
        double n_;

        Node(const State &state) : state_(state), w_(0), n_(0) {}
        void expand();
        double evaluate();
        Node &nextChildNode();
    };
    int thunderSearchAction(const State &state, const int playout_number);
}

#endif //AI_SEARCH_THUNDER_H
