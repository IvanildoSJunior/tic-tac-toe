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
        class Position
    {
        public:
            int x;
            int y;
            bool isLegal(Board board);
            
    };

        class Iterator
        {
            public:
            Position operator*();
            Iterator operator++();
            Iterator operator++(int);
            bool operator!=(Iterator other);
        };

        Board(int dimension): board(dimension * dimension,EMPTY){}
        void display();
        char winner();
        Iterator begin();
        Iterator end(); 
    

    

};
#endif


