#ifndef AI_SEARCH_AUTOMOVEMAZESTATE_H
#define AI_SEARCH_AUTOMOVEMAZESTATE_H

#include "Pos.h"
#include <string>
#include <vector>
using ci = const int;
ci dx[4] = {1, -1, 0, 0};
ci dy[4] = {0, 0, 1, -1};

class AutoMoveMazeState {
private:
    std::vector<std::vector<int>> Maze;
    std::vector<Pos> character;
public:
    int game_score_, character_num, turn_, H, W, END_TURN, seed;
    int64_t evaluated_score_;

    AutoMoveMazeState(ci H, ci W, ci END_TURN, ci character_num, ci seed);
    void setCharacter(ci character_id, ci y, ci x);
    bool isDone() const;
    std::string toString() const;
    int64_t getScore(bool is_print = false);
    void movePlayer(ci character_id);
    void advance();
    void init();
    void transition();
};


#endif //AI_SEARCH_AUTOMOVEMAZESTATE_H
