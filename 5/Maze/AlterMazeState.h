#ifndef AI_SEARCH_ALTERMAZESTATE_H
#define AI_SEARCH_ALTERMAZESTATE_H
#include <vector>
#include <random>
#include "Character.h"

constexpr const int H = 3;
constexpr const int W = 3;
constexpr const int END_TURN = 4;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

enum WinningStatus
{
    WIN,
    LOSE,
    DRAW,
    NONE,
};

class AlterMazeState {
private:
    std::vector<std::vector<int>> Maze;
    std::vector<Character> cl;
    int turn_;
    bool isFirstPlayer() const;
public:
    std::mt19937 mt_for_construct;
    int seed;
    AlterMazeState();
    AlterMazeState(const int seed);
    bool isDone() const;
    void advance(const int action);
    std::vector<int> legalActions() const;
    std::string toString() const;
    WinningStatus getWinningStatus() const;
    int64_t getScore() const;
    double getFirstPlayerScoreForWinRate() const;
};

using State = AlterMazeState;

using AIFunction = std::function<int(const State &)>;
using StringAIPair = std::pair<std::string, AIFunction>;

void testFirstPlayerWinRate(const std::array<StringAIPair, 2> &ais, const int game_number);

#endif //AI_SEARCH_ALTERMAZESTATE_H
