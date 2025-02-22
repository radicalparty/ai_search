#include "thunder.h"
#include <cassert>

using Node = thunder::Node;

double Node::evaluate(){
    if (this->state_.isDone()){
        double value = 0.5;
        switch (this->state_.getWinningStatus()) {
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

    if (this->child_nodes_.empty()){
        double value = this->state_.getScoreRate();
        this->w_ += value;
        ++this->n_;

        this->expand();

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
    for (const auto action : legal_actions)
    {
        this->child_nodes_.emplace_back(this->state_);
        this->child_nodes_.back().state_.advance(action);
    }
}

Node &Node::nextChildNode() {
    for (auto &child_node: this->child_nodes_){
        if (child_node.n_ == 0){
            return child_node;
        }
    }
    double t = 0;
    for (const auto &child_node : this->child_nodes_){
        t += child_node.n_;
    }

    double best_value = -INF;
    int best_action_index = -1;
    for (int i = 0; i < this->child_nodes_.size(); i++){
        const auto &child_node = this->child_nodes_[i];

        double thunder_value = 1. - child_node.w_ / child_node.n_;

        if (thunder_value > best_value){
            best_action_index = i;
            best_value = thunder_value;
        }
    }

    return this->child_nodes_[best_action_index];
}

int thunder::thunderSearchAction(const State &state, const int playout_number) {
    Node root_node = Node(state);
    root_node.expand();
    for (int i = 0; i < playout_number; i++)
    {
        root_node.evaluate();
    }
    auto legal_actions = state.legalActions();

    int best_action_searched_number = -1;
    int best_action_index = -1;
    assert(legal_actions.size() == root_node.child_nodes_.size());
    for (int i = 0; i < legal_actions.size(); i++)
    {
        int n = root_node.child_nodes_[i].n_;
        if (n > best_action_searched_number)
        {
            best_action_index = i;
            best_action_searched_number = n;
        }
    }
    return legal_actions[best_action_index];
}