#ifndef AI_SEARCH_CHARACTER_H
#define AI_SEARCH_CHARACTER_H

struct Character{
    int y, x, game_score_;
    Character();
    Character(const int y = 0, const int x = 0);
    bool operator==(Character other) const;
};

#endif //AI_SEARCH_CHARACTER_H
