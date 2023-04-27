#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#include <vector>

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const int dimension = 3;

class Board
{
    private:
        std::vector<char> board;
    public:
        Board(int dimension): board(dimension * dimension,EMPTY){}
        void display();
        char winner();
};
#endif


