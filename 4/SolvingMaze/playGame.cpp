#include "playGame.h"

void playGame(const StringAIPair &ai, int seed){
    State state(5, 5, 5, 3, seed);
    state = ai.second(state);
    std::cout << state.toString() << std::endl;
    auto score = state.getScore(true);
    std::cout << "Score of " << ai.first << ": " << score << std::endl;
}