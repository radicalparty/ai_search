#include <iostream>
#include "SolvingMaze/GreedySearch.h"
#include "SolvingMaze/RandomSearch.h"
#include "SolvingMaze/BeamSearch.h"

using State = MazeState;

void testAiScore(int game_number, int seed);

int main() {
    testAiScore(10, 0);
    return 0;
}

void testAiScore(int game_number, int seed){
    std::mt19937 mt_for_construct(seed);
    double rnd = 0.0, grd = 0.0, beam = 0.0;
    for (int i = 0; i < game_number; i++){
        auto state = State(3, 4, 4, (int)mt_for_construct());

        auto rndState = state;

        while (!rndState.isDone()){
            rndState.advance(randomAction(rndState));
        }

        rnd += rndState.game_score_;

        auto grdState = state;

        while (!grdState.isDone()){
            grdState.advance(greedyAction(grdState));
        }

        grd += rndState.game_score_;

        auto beamState = state;

        while (!beamState.isDone()){
            beamState.advance(beamSearchAction(beamState, 3, 4));
        }

        beam += beamState.game_score_;
    }

    std::cout << " Random: " << rnd / game_number << "\n Greedy: " << grd / game_number << "\n Beam: " << beam / game_number;
}