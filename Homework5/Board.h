//
// Created by Ege Tan on 9.05.2024.
//
#ifndef HOMEWORK5_BOARD_H
#define HOMEWORK5_BOARD_H
#include <iostream>
#include <string>

class Board
{
private:
    char** board_matrix;
    int N;
    int size;
    void drop();
    bool check_winner(const char&);
public:
    Board(const int&,const int&);
    ~Board();
    void print_board();
    bool put_piece(const char&,const int&);
    void turn_board_clockwise();
    char get_game_status();
};


#endif //HOMEWORK5_BOARD_H
