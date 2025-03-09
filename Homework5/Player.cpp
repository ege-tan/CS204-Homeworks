//
// Created by Ege Tan on 9.05.2024.
//
#include "Player.h"

//constructor (_myboard is in initializer list)
Player::Player(Board & _myboard, const char & _game_piece) : myboard(_myboard)
{
    game_piece = _game_piece;
}

//if smth succesfully inserted returns ture , otherwise returns false.
bool Player::put(const int & col)
{
    if(myboard.put_piece(game_piece,col))
    {
        return true;
    }
    return false;
}

//turn the board 90 degree.
void Player::turn_board()
{
    myboard.turn_board_clockwise();
}

//get the current symbol of player object
char Player::get_symbol() const
{
    return game_piece;
}

//returns true if the current player is winner of the game
bool Player::is_winner()
{
    if (myboard.get_game_status() == game_piece)
    {
        return true;
    }
    return false;
}

