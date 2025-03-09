//
// Created by Ege Tan on 9.05.2024.
//
#include "Board.h"

//constructor for creating new table
Board::Board(const int & _size, const int & _n)
{
    size = _size;
    N = _n;
    //array of pointers that points to char
    board_matrix = new  char* [size];
    //create new arrays for each element in pointer matrix
    for (int i = 0; i < size; ++i)
    {
        board_matrix[i] = new char [size];
    }
    //assigning every element to '-'
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            board_matrix[i][j] = '-';
        }
    }
}

//destructor , deallocate every dynamically allocated memory from heap
Board::~Board()
{
    for (int i = 0; i < size; ++i)
    {
        delete [] board_matrix[i];
    }
    delete board_matrix;
}

//prints the board elements
void Board::print_board()
{
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size ; ++j)
        {
            std::cout << board_matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//puts piece to the first row of the specific column
//then by calling drop function , I applied the gravitiy effect with drop function.
bool Board::put_piece(const char & ch, const int & col)
{
    if (col < size)
    {
        if (board_matrix[0][col] == '-')
        {
            board_matrix[0][col] = ch;
            drop();
            return true;
        }
    }
    return false;
}

//appliying gravitiy force
void Board::drop()
{
    int row;
    //for each column
    for (int i = 0; i < size; ++i)
    {
        //for each row in that column (starting from the bottom to top)
        for (int j = size-1; j > -1; --j)
        {
            if (board_matrix[j][i] != '-')
            {
                row = j;
                //start from the bottom one and check wheter there is
                //empty cell for gravity force
                while (row < size-1 && board_matrix[row+1][i] == '-')
                {
                    board_matrix[row+1][i] = board_matrix[row][i];
                    board_matrix[row][i] = '-';
                    row++;
                }
            }
        }
    }
}

//turn the matrix 90 degree to clockwise
void Board::turn_board_clockwise()
{
    for (int layer = 0; layer < size / 2; ++layer) {
        int first = layer;
        int last = size - layer - 1;
        for (int i = first; i < last; ++i) {
            int ofset = i - first;
            char top = board_matrix[first][i];
            // Move left to top
            board_matrix[first][i] = board_matrix[last - ofset][first];
            // Move bottom to left
            board_matrix[last - ofset][first] = board_matrix[last][last - ofset];
            // Move right to bottom
            board_matrix[last][last - ofset] = board_matrix[i][last];
            // Move top to right
            board_matrix[i][last] = top;
        }
    }
    drop();
}

//returns the game status as char
char Board::get_game_status()
{
    if(check_winner('X'))//cheks wheter x is the winner or not
    {
        if(check_winner('O'))//cheks wheter o is also a winner or not
        {
            return 'D';//if both of them are winner
        }
        else
        {
            return 'X';//o is not winner , so only winner is x
        }
    }
    else//if x is not the winner
    {
        if(check_winner('O'))//cheks wheter o is also a winner or not
        {
            return 'O';//return O as the only winner
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    if (board_matrix[i][j] == '-')
                    {
                        return '-';//if there is still empty space in matrix
                    }
                }
            }
            return 'D';//there is no empty space and draw occurs
        }
    }
}

//helper function that cheks for winner
bool Board::check_winner(const char & ch)
{
    std::string searching = "";//string for searching
    std::string board_matrix_string = "";//every occurence of strings in matrix
    for (int i = 0; i < N; ++i)
    {
        searching+=ch;//searching matrix is multiplied by N.
    }
    //taking all rows from matrix to string
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            board_matrix_string+= board_matrix[i][j];
        }
        board_matrix_string+=" ";
    }
    //taking all colums from matrix to string
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            board_matrix_string+= board_matrix[j][i];
        }
        board_matrix_string+=" ";
    }
    //taking all diagonals from matrix to string
    //upper-right diagonals
    for (int i = 0; i < size; ++i)
    {
        int row = 0; // Start from the first row
        int col = i; // Start from column i
        while (col < size && row < size)
        {
            board_matrix_string += board_matrix[row][col];
            row++;
            col++;
        }
        board_matrix_string+=" ";
    }
    //bottom left diagonals
    for (int i = 0; i < size; ++i)
    {
        int row = size - 1; // Start from the last row
        int col = i; // Start from column i
        while (col >= 0 && row >= 0)
        {
            board_matrix_string += board_matrix[row][col];
            row--;
            col--;
        }
        board_matrix_string+=" ";
    }
    //upper-left diagonals
    for (int i = 0; i < size; ++i)
    {
        int row = 0; // Start from the first row
        int col = i; // Start from column i
        while (col >= 0 && row < size)
        {
            board_matrix_string += board_matrix[row][col];
            row++;
            col--;
        }
        board_matrix_string+=" ";
    }
    //bottom-right diagonlas
    for (int i = 0; i < size; ++i)
    {
        int row = size - 1; // Start from the last row
        int col = i; // Start from column i
        while (col < size && row >= 0)
        {
            board_matrix_string += board_matrix[row][col];
            row--;
            col++;
        }
        board_matrix_string+=" ";
    }
    //if searching item is found in matrix
    if (board_matrix_string.find(searching) != std::string::npos)
    {
        return true;
    }
    return false;
}

