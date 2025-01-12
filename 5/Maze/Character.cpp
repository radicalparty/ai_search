#include "Character.h"

Character::Character(): x(0), y(0), game_score_(0) {}

Character::Character(const int y, const int x): x(x), y(y), game_score_(0) {}

bool Character::operator==(Character other) const {
    return (x == other.x) && (y == other.y);
}