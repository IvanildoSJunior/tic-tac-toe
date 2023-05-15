#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include "board.hpp"
#include <utility>

class Player
{   
    public:
        virtual std::pair<int, int> play(Board board, char piece) = 0;
    
        virtual void announceIWon(char piece);
};
#endif