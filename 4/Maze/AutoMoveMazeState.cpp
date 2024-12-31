#include "AutoMoveMazeState.h"
#include <random>
#include <iostream>
#include <sstream>

#define INF 1e9

AutoMoveMazeState::AutoMoveMazeState(ci H, ci W, ci END_TURN, ci character_num, ci seed) {
    //construct the maze
    this->H = H; this->W = W; this->END_TURN = END_TURN; this->character_num = character_num;
    this->turn_ = 0; this->game_score_ = 0; this->evaluated_score_ = 0; this->seed = seed;

    auto mt_for_construct = std::mt19937(seed);
    character.resize(character_num);
    Maze.resize(H, std::vector<int>(W, 0));

    for (int y = 0; y < H; y++){
        for (int x = 0; x < W; x++){
            Maze[y][x] = abs((int)mt_for_construct() % 9) + 1;
        }
    }
}

void AutoMoveMazeState::setCharacter(ci character_id, ci y, ci x){
    //setting character in maze

    this->character[character_id].y = y;
    this->character[character_id].x = x;
}

int64_t AutoMoveMazeState::getScore(bool is_print){
    //
    auto tmp_state = *this;

    for (auto &cha: this->character){
        auto& point = tmp_state.Maze[cha.y][cha.x];
        point = 0;
    }

    while (!tmp_state.isDone()){
        tmp_state.advance();
        if (is_print)
            std::cout << tmp_state.toString() << std::endl;

    }

    return tmp_state.game_score_;
}

void AutoMoveMazeState::movePlayer(ci character_id){
    //Moving Player in turn
    Pos& cha = this->character[character_id];

    int best_point = -INF;
    int best_action_index = 0;

    for (int action = 0; action < 4; action++){
        int tx = cha.x + dx[action];
        int ty = cha.y + dy[action];

        if (ty >= 0 && ty < H && tx >= 0 && tx < W) {
            auto pt = this->Maze[ty][tx];
            if (pt > best_point){
                best_action_index = action;
                best_point = pt;
            }
        }
    }

    cha.y += dy[best_action_index];
    cha.x += dx[best_action_index];
}

void AutoMoveMazeState::advance(){
    //playing a turn
    for (int character_id = 0; character_id < character_num; character_id++){
        movePlayer(character_id);
    }
    for (auto& cha: this->character){
        auto& pt = this->Maze[cha.y][cha.x];
        this->game_score_ += pt;
        pt = 0;
    }
    ++this->turn_;
}

std::string AutoMoveMazeState::toString() const{
    std::stringstream ss;
    ss << "turn:\t" << this->turn_ << "\n";
    ss << "score:\t" << this->game_score_ << "\n";
    auto board_chars = std::vector<std::vector<char>>(H, std::vector<char>(W, '.'));
    for (int h = 0; h < H; h++)
    {
        for (int w = 0; w < W; w++)
        {
            bool is_written = false; // 해당 좌표에 기록할 문자가 결정되었는지 여부

            for (const auto &cha : this->character)
            {
                if (cha.y == h && cha.x == w)
                {
                    ss << "@";
                    is_written = true;
                    break;
                }
                board_chars[cha.y][cha.x] = '@';
            }
            if (!is_written)
            {
                if (this->Maze[h][w] > 0)
                {
                    ss << Maze[h][w];
                }
                else
                {
                    ss << '.';
                }
            }
        }
        ss << '\n';
    }

    return ss.str();
}

bool AutoMoveMazeState::isDone() const
{
    return this->turn_ == END_TURN;
}

void AutoMoveMazeState::init(){
    std::mt19937 mt_for_construct(this->seed);
    for (auto& cha: this->character){
        cha.y = abs((int)mt_for_construct()) % H;
        cha.x = abs((int)mt_for_construct()) % W;
    }
}

void AutoMoveMazeState::transition(){
    std::mt19937 mt_for_select(this->seed);
    auto& cha = this->character[abs((int)mt_for_select()) % character_num];

    cha.y = abs((int)mt_for_select()) % H;
    cha.x = abs((int)mt_for_select()) % W;
}