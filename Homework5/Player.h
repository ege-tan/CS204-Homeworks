//
// Created by Ege Tan on 9.05.2024.
//
#ifndef HOMEWORK5_PLAYER_H
#define HOMEWORK5_PLAYER_H
#include <iostream>
#include "Board.h"

class Player
{
private:
    char game_piece;
    Board & myboard;
public:
    Player(Board&,const char&);
    bool put (const int&);
    void turn_board();
    char get_symbol() const;
    bool is_winner();
};


#endif //HOMEWORK5_PLAYER_H
