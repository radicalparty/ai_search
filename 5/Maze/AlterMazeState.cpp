#include "AlterMazeState.h"
#include <random>
#include <iostream>
#include <sstream>

bool AlterMazeState::isFirstPlayer() const{
    return this->turn_ % 2 == 0;
}

AlterMazeState::AlterMazeState(const int seed) {
    this->Maze.resize(H, std::vector<int>(W, 0));
    this->turn_ = 0; this->seed = seed;
    this->cl = std::vector<Character>({
                                              Character(H / 2, (W / 2) - 1), Character(H / 2, (W / 2) + 1)
                                      });

    mt_for_construct = std::mt19937(seed);

    for (int y = 0; y < H; y++){
        for (int x = 0; x < W; x++){
            int pt = abs((int)mt_for_construct()) % 10;

            if (Character(y, x) == cl[0] || Character(y, x) == cl[1]) continue;

            this->Maze[y][x] = pt;
        }
    }
}

double AlterMazeState::getFirstPlayerScoreForWinRate() const
{
    switch (this->getWinningStatus())
    {
        case (WinningStatus::WIN):
            if (this->isFirstPlayer())
            {
                return 1.;
            }
            else
            {
                return 0.;
            }
        case (WinningStatus::LOSE):
            if (this->isFirstPlayer())
            {
                return 0.;
            }
            else
            {
                return 1.;
            }
        default:
            return 0.5;
    }
}

bool AlterMazeState::isDone() const {
    return turn_ == END_TURN;
}

void AlterMazeState::advance(const int action){
    auto& c = this->cl[0];
    c.x += dx[action];
    c.y += dy[action];
    auto& pt = this->Maze[c.y][c.x];
    if (pt > 0){
        c.game_score_ += pt; pt = 0;
    }
    this->turn_++;
    std::swap(this->cl[0], this->cl[1]);
}

std::vector<int> AlterMazeState::legalActions() const{
    std::vector<int> actions;
    const auto& c = this->cl[0];
    for (int action = 0; action < 4; action++){
        int ty = c.y + dy[action];
        int tx = c.x + dx[action];
        if (ty >= 0 && ty < H && tx >= 0 && tx < W)
            actions.emplace_back(action);

    }
    return actions;
}

WinningStatus AlterMazeState::getWinningStatus() const{
    if (isDone())
    {
        if (cl[0].game_score_ > cl[1].game_score_)
            return WinningStatus::WIN;
        else if (cl[0].game_score_ < cl[1].game_score_)
            return WinningStatus::LOSE;
        else
            return WinningStatus::DRAW;
    }
    else
    {
        return WinningStatus::NONE;
    }
}

std::string AlterMazeState::toString() const{
    std::stringstream ss("");
    ss << "turn:\t" << this->turn_ << "\n";
    for (int player_id = 0; player_id < this->cl.size(); player_id++)
    {
        int actual_player_id = player_id;
        if (this->turn_ % 2 == 1)
        {
            actual_player_id = (player_id + 1) % 2; // 홀수 턴은 초기 배치 시점에서 보면 player_id가 반대
        }
        const auto &chara = this->cl[actual_player_id];
        ss << "score(" << player_id << "):\t" << chara.game_score_ << "\ty: " << chara.y << " x: " << chara.x << "\n";
    }
    for (int h = 0; h < H; h++)
    {
        for (int w = 0; w < W; w++)
        {
            bool is_written = false; // 해당 좌표에 기록할 문자가 결정되었는지 여부
            for (int player_id = 0; player_id < this->cl.size(); player_id++)
            {
                int actual_player_id = player_id;
                if (this->turn_ % 2 == 1)
                {
                    actual_player_id = (player_id + 1) % 2; // 홀수 턴은 초기 배치 시점에서 보면 player_id가 반대
                }

                const auto &character = this->cl[player_id];
                if (character.y == h && character.x == w)
                {
                    if (actual_player_id == 0)
                    {
                        ss << 'A';
                    }
                    else
                    {
                        ss << 'B';
                    }
                    is_written = true;
                }
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

int64_t AlterMazeState::getScore() const {
    return cl[0].game_score_ - cl[1].game_score_;
}

// 게임을 game_number×2(선공과 후공을 교대)횟수만큼 플레이해서 ais의 0번째에 있는 AI 승률을 표시한다.
void testFirstPlayerWinRate(const std::array<StringAIPair, 2> &ais, const int game_number)
{
    using std::cout;
    using std::endl;

    double first_player_win_rate = 0;
    for (int i = 0; i < game_number; i++)
    {
        auto base_state = State(i);
        for (int j = 0; j < 2; j++)
        { // 공평하게 선공과 후공을 교대함
            auto state = base_state;
            auto &first_ai = ais[j];
            auto &second_ai = ais[(j + 1) % 2];
            while (true)
            {
                state.advance(first_ai.second(state));
                if (state.isDone())
                    break;
                state.advance(second_ai.second(state));
                if (state.isDone())
                    break;
            }
            double win_rate_point = state.getFirstPlayerScoreForWinRate();
            if (j == 1)
                win_rate_point = 1 - win_rate_point;
            if (win_rate_point >= 0)
            {
                state.toString();
            }
            first_player_win_rate += win_rate_point;
        }
        cout << "i " << i << " w " << first_player_win_rate / ((i + 1) * 2) << endl;
    }
    first_player_win_rate /= (double)(game_number * 2);
    cout << "Winning rate of " << ais[0].first << " to " << ais[1].first << ":\t" << first_player_win_rate << endl;
}