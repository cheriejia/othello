#include "player.hpp"
#include <iostream>
using namespace std;
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */

/* 
    Team: Ruthwick and Sathwick 
    Members: Juliette Xiong and Cherie Jia
*/
Player::Player(Side side) 
{
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    // Initialize new board
    b = new Board();
    mySide = side;

}

/*
 * Destructor for the player.
 */
Player::~Player() 
{
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
    // Make move according to whether my AI is black or white.
    if (opponentsMove != nullptr)
    {
        if (mySide == BLACK)
        {
            b->doMove(opponentsMove, WHITE);
        }
        else
        {
            b->doMove(opponentsMove, BLACK);
        }
    }


    
    if (!(b->hasMoves(mySide)))
    {
        return nullptr;
    }

    Move *movegood = nullptr;
    int goodcount = 0;
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            Move *move = new Move(i, j);
            Board *goodb = b->copy();
            if (goodb->checkMove(move, mySide))
            {
                goodb->doMove(move, mySide);
                // Implement our heuristic when making moves.
                if (movegood == nullptr || goodb->hot(mySide) > goodcount)

                    {

                        movegood = move;
                        goodcount =  goodb->hot(mySide);
                    }
            }
        }
    }
    // Make move if it is legal
    if (movegood != nullptr && b->checkMove(movegood, mySide))
    {
        b->doMove(movegood, mySide);
    }
    


    return movegood;
}
