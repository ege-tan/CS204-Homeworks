//Ege Tan , 00030977 , 03.02.2024
//Homework1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//This function takes a matrix as a parameter
//prints the each element of that matrix.
void print(const vector <vector <char>> & table)
{
    for (unsigned int i = 0;i< table.size();i++)
    {
        for (unsigned int j = 0; j <table[i].size() ; j++)
        {
            cout << table[i][j];
        }
        cout << endl;
    }
}
//This function takes a matrix , direction and index inputs as a parameter
//returns -1 if path is fully empty otherwise returns the first obstacle's inedx
int path_check(const vector <vector <char>> & table , string direction , int row , int col )
{
    if (direction == "up")
    {
        for (int i = row-1; i > -1 ; i--)
        {
            if (table[i][col] != '-')
            {
                return i;//returns the obstacle's index
            }
        }
        return -1;
    }
    else if (direction == "down")
    {
        for (int i = row+1; i < table.size() ; i++)
        {
            if (table[i][col] != '-')
            {
                return i;//returns the obstacle's index
            }
        }
        return -1;
    }
    else if (direction == "left")
    {
        for (int i = col-1; i > -1 ; i--)
        {
            if (table[row][i] != '-')
            {
                return i;//returns the obstacle's index
            }
        }
        return -1;
    }
    else if (direction == "right")
    {
        for (int i = col+1; i < table[0].size() ; i++)
        {
            if (table[row][i] != '-')
            {
                return i;//returns the obstacle's index
            }
        }
        return -1;
    }
    return -1;
}
//This function takes a matrix and input coordinates as a parameter
//changes the matrix accordingly.
void move (vector <vector <char>> & table , int row , int col)
{
    if (table[row][col] == 'u')
    {
        if(row == 0)//checks if this index is in border
        {
            table[row][col] = '-';//change index with '-'
        }
        else
        {
            if (path_check(table,"up",row,col) == -1)//if the direction of the index is totally empty
            {
                table[row][col] = '-';//change the current index with '-'
            }
            else
            {
                if (path_check(table,"up",row,col) == row-1)// if the next index is not '-'
                {
                    cout << "No tiles have been moved." << endl;
                    return;
                }
                else
                {
                    table[row][col] = '-';//change current index with '-'
                    table[path_check(table,"up",row,col)+1][col] = 'u';//change the last index before the obstacle with adequate letter.
                }
            }
        }
        cout << "Tile at " << "(" << row << "," << col << ")"<<" has been moved."<< endl;
    }
    else if (table[row][col] == 'd')
    {
        if(row == table.size()-1)//checks if this index is in border
        {
            table[row][col] = '-';//change index with '-'
        }
        else
        {
            if (path_check(table,"down",row,col) == -1)//if the direction of the index is totally empty
            {
                table[row][col] = '-';//change the current index with '-'
            }
            else
            {
                if (path_check(table,"down",row,col) == row+1)// if the next index is not '-'
                {
                    cout << "No tiles have been moved." << endl;
                    return ;
                }
                else
                {
                    table[row][col] = '-';//change current index with '-'
                    table[path_check(table,"down",row,col)-1][col] = 'd';//change the last index before the obstacle with adequate letter.
                }
            }
        }
        cout << "Tile at " << "(" << row << "," << col << ")"<<" has been moved."<< endl;
    }
    else if (table[row][col] == 'l')
    {
        if(col == 0)//checks if this index is in border
        {
            table[row][col] = '-';//change index with '-'
        }
        else
        {
            if (path_check(table,"left",row,col) == -1)//if the direction of the index is totally empty
            {
                table[row][col] = '-';//change the current index with '-'
            }
            else
            {
                if (path_check(table,"left",row,col) == col-1)// if the next index is not '-'
                {
                    cout << "No tiles have been moved." << endl;
                    return;
                }
                else
                {
                    table[row][col] = '-';//change current index with '-'
                    table[row][path_check(table,"left",row,col)+1] = 'l';//change the last index before the obstacle with adequate letter.
                }
            }
        }
        cout << "Tile at " << "(" << row << "," << col << ")"<<" has been moved."<< endl;
    }
    else if (table[row][col] == 'r')
    {
        if(col == table[0].size())//checks if this index is in border
        {
            table[row][col] = '-';//change index with '-'
        }
        else
        {
            if (path_check(table,"right",row,col) == -1)//if the direction of the index is totally empty
            {
                table[row][col] = '-';//change the current index with '-'
            }
            else
            {
                if (path_check(table,"right",row,col) == col+1)
                {
                    cout << "No tiles have been moved." << endl;
                    return;
                }
                else
                {
                    table[row][col] = '-';//change current index with '-'
                    table[row][path_check(table,"right",row,col)-1] = 'r';//change the last index before the obstacle with adequate letter.
                }
            }
        }
        cout << "Tile at " << "(" << row << "," << col << ")"<<" has been moved."<< endl;
    }
    else
    {
        cout << "No tiles have been moved." << endl;
    }
}
//This function takes a matrix as a parameter
//checks wheter there is a possible move or not.
bool matrix_movement_check(const vector <vector <char>> & table)
{
    int row = table.size();
    int col = table[0].size();

    for (int i = 0;i< table.size();i++)
    {
        for (int j = 0; j <table[i].size() ; j++)
        {
            //for each element of matrix
            //according to directions
            if (table[i][j] == 'u')
            {
                if (i-1 > -1)//checks the borders
                {
                    if (table[i-1][j] == '-')//checks the next index
                    {
                        return true;//if it is '-' --> there is possible movement
                    }
                }
                else
                {
                    return true;
                }
            }
            else if (table[i][j] == 'd')
            {
                if (i+1 < row)//checks the borders
                {
                    if (table[i+1][j] == '-')//checks the next index
                    {
                        return true;//if it is '-' --> there is possible movement
                    }
                }
                else
                {
                    return true;
                }
            }
            else if (table[i][j] == 'l')
            {
                if (j-1 > -1)//checks the borders
                {
                    if (table[i][j-1] == '-')//checks the next index
                    {
                        return true;//if it is '-' --> there is possible movement
                    }
                }
                else
                {
                    return true;
                }
            }
            else if (table[i][j] == 'r')
            {
                if (i+1 < col)//checks the borders
                {
                    if (table[i][j+1] == '-')//checks the next index
                    {
                        return true;//if it is '-' --> there is possible movement
                    }
                }
                else
                {
                    return true;
                }
            }
        }
    }
    cout << "No more moves are possible." << endl;
    return false;
}
//This function takes a matrix as a parameter
//returns wheter it contains only "-" or not.
bool matrix_empty_check(const vector <vector <char>> & table)
{
    for (unsigned int i = 0;i< table.size();i++)
    {
        for (unsigned int j = 0; j <table[i].size() ; j++)
        {
            if (table[i][j] != '-')
            {
                return false;
            }
        }
    }
    cout << "The matrix is empty." << endl;
    return true;
    //returns true if matrix is empty.
}
//This function takes a matrix and a filestream as a parameters
//adds each line of file to the matrix.
void add_to_matrix(ifstream & file_input , vector <vector <char>> & table)
{
    string line;
    vector <char> row;
    while(getline(file_input,line))
    {
        //add chars to vector
        for(unsigned int i = 0; i < line.length(); ++i) {
            row.push_back(line.at(i));
        }
        //add vector to matrix as a row
        table.push_back(row);
        row.clear();
    }
}
//This function takes a filestream as a parameter
//returns wheter a file is in a correct format or not.
bool file_check(ifstream & file_input)
{
    unsigned int char_number = 0;
    int line_number = 0;
    string line;
    while(getline(file_input,line))
    {
        for (char c : line)
        {
            //controls the chars
            if(c != 'd' && c != 'u' && c != 'l' && c != 'r' && c != '-')
            {
                return false;
            }
            //if a char is not any of the chars from the selections , returns false.
        }
        //takes the first lines length
        if (line_number == 0)
        {
            char_number = line.length();
        }
        else
        {
            //compare first line's length with other one's.
            if (line.length()!=char_number)
            {
                return false;
            }
        }
        //increases the line number.
        line_number++;
    }
    //prepare file for new read.
    file_input.clear();
    file_input.seekg(0);
    return true;
}
int main()
{
    int row_input , col_input;
    vector <vector < char > > main_table;
    ifstream file_input;
    string file_name;
    bool check;
    cout << "Please enter the file name:"<<endl;
    //file input check part
    do
    {
        cin >> file_name;
        file_input.open(file_name.c_str());
        if (file_input.fail())
        {
            cout << "Could not open the file. Please enter a valid file name:"<<endl;
            check = true;
        }
        else
        {
            check = false;
        }
    }while(check);
    //*********************
    if (!file_check(file_input))
    {
        cout << "Erroneous file content. Program terminates."<< endl;
    }
    else
    {
        add_to_matrix(file_input,main_table);
        cout << "The matrix file contains:"<<endl;
        print(main_table);
        while (!matrix_empty_check(main_table) && matrix_movement_check(main_table))
        {
            cout << "Please enter the row and column of the tile that you want to move:"<<endl;
            cin >> row_input >> col_input;
            if ((row_input > -1 && row_input < main_table.size()) && (col_input > -1 && col_input < main_table[0].size()))//check wheter index inputs are in matrix or not.
            {
                move(main_table,row_input,col_input);
                print(main_table);
            }
            else
            {
                cout << "Invalid row or column index."<< endl;
            }
        }
    }
    return 0;
}
