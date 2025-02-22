#include "play.h"
#include "minimax.h"

using State = AlterMazeState;

void playGame(const int seed)
{
    using std::cout;
    using std::endl;
    auto state = State(seed);
    cout << state.toString() << endl;
    while (!state.isDone())
    {
        // 1p
        {
            cout << "1p ------------------------------------" << endl;
            int action = minimax::miniMaxAction(state, END_TURN);
            cout << "action " << action << endl;
            state.advance(action); // (a-1) 여기서 시점이 바뀌어서 2p 시점이 된다.
            cout << state.toString() << endl;
            if (state.isDone())
            {

                switch (state.getWinningStatus()) // (a-2) a-1에서 2p 시점이 되었으므로 WIN이라면 2p가 승리
                {
                    case (WinningStatus::WIN):
                        cout << "winner: "
                             << "2p" << endl;
                        break;
                    case (WinningStatus::LOSE):
                        cout << "winner: "
                             << "1p" << endl;
                        break;
                    default:
                        cout << "DRAW" << endl;
                        break;
                }
                break;
            }
        }
        // 2p
        {
            cout << "2p ------------------------------------" << endl;
            int action = randomAction(state);
            cout << "action " << action << endl;
            state.advance(action); // (b-1) 여기서 시점이 바뀌어서 1p 시점이 된다.
            cout << state.toString() << endl;
            if (state.isDone())
            {

                switch (state.getWinningStatus()) // (b-2) b-1에서 1p 시점이 되었으므로 WIN이라면 1p가 승리
                {
                    case (WinningStatus::WIN):
                        cout << "winner: "
                             << "1p" << endl;
                        break;
                    case (WinningStatus::LOSE):
                        cout << "winner: "
                             << "2p" << endl;
                        break;
                    default:
                        cout << "DRAW" << endl;
                        break;
                }
                break;
            }
        }
    }
}