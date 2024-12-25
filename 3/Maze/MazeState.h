#ifndef MAZESTATE_H
#define MAZESTATE_H

#include <vector>
#include <string>
#include <sstream>
#include <random>
#include "Pos.h"

// Class to represent the state of the maze game
class MazeState {
private:
    int64_t evaluated_score = 0;      // Evaluated score for the maze state
    int H, W;                         // Height and width of the maze
    std::vector<std::vector<int>> Maze; // 2D grid representing the maze
    int turn_ = 0, END_TURN;          // Current turn and total turns allowed
    const int dx[4] = {0, 1, 0, -1};  // Movement in the x-direction
    const int dy[4] = {1, 0, -1, 0};  // Movement in the y-direction

public:
    Pos position = Pos(0, 0);         // Player's position in the maze
    int game_score_ = 0;              // Game score accumulated

    // Default constructor
    MazeState();

    // Constructor to initialize the maze
    MazeState(int H, int W, int END_TURN, int seed);

    // Check if the game is over
    bool isDone() const;

    // Advance the game state based on the given action
    void advance(const int action);

    // Get a list of legal actions
    std::vector<int> legalActions() const;

    // Convert the current state of the maze to a string
    std::string toString() const;

    // Evaluate and update the score
    void evaluateScore();
};

#endif // MAZESTATE_H
