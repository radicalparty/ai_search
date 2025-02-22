#include <cassert>
#include "montecarlo.h"

double montecarlo::playout(State *state) {//한 판을 무작위로 플레이해서 행동 가치를 계산
    switch (state->getWinningStatus()){
        case (WinningStatus::WIN):
            return 1.;
        case (WinningStatus::LOSE):
            return 0.;
        case (WinningStatus::DRAW):
            return 0.5;
        default:
            state->advance(randomAction(*state));
            return 1. - playout(state);
    }
}

int montecarlo::primitiveMontecarloAction(const State &state, int playout_number) {
    auto legal_actions = state.legalActions();
    auto values = std::vector<double>(legal_actions.size());
    auto cnts = std::vector<double>(legal_actions.size());

    for (int cnt = 0; cnt < playout_number; cnt++){//이기고 진 횟수를 측정
        int index = cnt % legal_actions.size();

        State next_state = state;
        next_state.advance(legal_actions[index]);

        values[index] += 1. - playout(&next_state);
        ++cnts[index];
    }

    int best_action_index = -1;
    double best_score = -INF;

    for (int index = 0; index < legal_actions.size(); index++){
        double value_mean = values[index] / cnts[index];
        if (value_mean > best_score){
            best_score = value_mean;
            best_action_index = index;
        }
    }
    return legal_actions[best_action_index];
}

using Node = mcts::Node;

double Node::evaluate() {
    //if game is end: 승패에 따라 누적 가치 더하고 누적 가치 반환
    if (this->state_.isDone()){
        double value = 0.5;
        switch (this->state_.getWinningStatus()){
            case (WinningStatus::WIN):
                value = 1.; break;
            case (WinningStatus::LOSE):
                value = 0.; break;
            default:
                break;
        }
        this->w_ += value;
        ++this->n_;
        return value;
    }

    //자식 노드가 존재하지 않는 경우: 플레이 아웃 결과를 누적 가치에 더하고 누적 가치를 반환. 시행 횟수가 임계치를 넘으면 자식 노드 확장
    if (this->child_nodes_.empty()){
        State state_copy = this->state_;
        double value = montecarlo::playout(&state_copy);
        this->w_ += value;
        ++this->n_;

        if (this->n_ == EXPAND_THRESHOLD) this->expand();

        return value;
    }

    else{
        double value = 1. - this->nextChildNode().evaluate();
        this->w_ += value;
        ++this->n_;
        return value;
    }
}

void Node::expand(){
    auto legal_actions = this->state_.legalActions();
    this->child_nodes_.clear();
    for (const auto action: legal_actions){
        this->child_nodes_.emplace_back(this->state_);
        this->child_nodes_.back().state_.advance(action);
    }
}

Node& Node::nextChildNode() {
    for (auto& child_node: this->child_nodes_){
        if (child_node.n_ == 0){
            return child_node;
        }
    }
    double t = 0;
    for (const auto &child_node: this->child_nodes_){
        t += child_node.n_;
    }

    double best_value = -INF;
    int best_action_index = -1;
    for (int i = 0; i < this->child_nodes_.size(); i++){
        const auto &child_node = this->child_nodes_[i];
        double ucb1_value = 1. - child_node.w_ / child_node.n_ + (double)C * std::sqrt(2. * std::log(t) / child_node.n_);

        if (ucb1_value > best_value){
            best_action_index = i; best_value = ucb1_value;
        }
    }

    return this->child_nodes_[best_action_index];
}

int mcts::mctsAction(const State &state, const int playout_number) {
    Node root_node = Node(state);
    root_node.expand();
    for (int i = 0; i < playout_number; i++){
        root_node.evaluate();
    }
    auto legal_actions = state.legalActions();

    int best_action_searched_number = -1;
    int best_action_index = -1;
    assert(legal_actions.size() == root_node.child_nodes_.size());
    for (int i = 0; i < legal_actions.size(); i++){
        int n = root_node.child_nodes_[i].n_;
        if (n > best_action_searched_number){
            best_action_index = i;
            best_action_searched_number = n;
        }
    }
    return legal_actions[best_action_index];
}