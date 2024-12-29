#include <random>
#include <vector>
#include <string>
#include <sstream>
#include "Pos.h"
#include "MazeState.h"

MazeState::MazeState() {}

MazeState::MazeState(int H, int W, int END_TURN, int seed) {//construct the maze
        this->H = H; this->W = W; this->END_TURN = END_TURN;
        std::mt19937 mt_for_construct(seed); //seed for constructing the maze
        position.y = mt_for_construct() % H;
        position.x = mt_for_construct() % W;
        Maze = std::vector<std::vector<int > >(H, std::vector<int>(W, 0)); //Maze is initialized with 0

        for(int i = 0; i < H; i++){
            for(int j = 0; j < W; j++){
                Maze[i][j] = mt_for_construct() % 10; //randomly set the value of the maze
            }
        }
}

bool MazeState::isDone() const{
    return this->turn_ == END_TURN;
}

void MazeState::advance(const int action){//move the point by the action
        this->position.x += dx[action]; this->position.y += dy[action];
        auto& current = this->Maze[this->position.y][this->position.x];

        if (current > 0){
            this->game_score_ += current; current = 0;
        }

        this->turn_++;
    }

std::vector<int> MazeState::legalActions() const{//return the legal actions
        std::vector<int> actions;
        for(int i = 0; i < 4; i++){
            int nx = this->position.x + dx[i], ny = this->position.y + dy[i];
            if(nx >= 0 && nx < W && ny >= 0 && ny < H){
                actions.push_back(i);
            }
        }
        return actions;
}

std::string MazeState::toString() const{//return the string of the maze
        std::stringstream ss;
        ss << "Turn:\t" << this->turn_ << " Score:" << this->game_score_ << "\n";
        ss << "Score:\t" << this->game_score_ << "\n";
        for (int h = 0; h < H; h++){
            for (int w = 0; w < W; w++){
                if (this->position.x == w && this->position.y == h){
                    ss << "P";
                }else if (this->Maze[h][w] > 0){
                    ss << this->Maze[h][w];
                }
                else{
                    ss << ".";
                }
            }
            ss << "\n";
        }
        return ss.str();
}

void MazeState::evaluateScore(){
    this->evaluated_score = this->game_score_;
}

bool MazeState::operator<(const MazeState& maze_2) const{
    return this->evaluated_score < maze_2.evaluated_score;
}