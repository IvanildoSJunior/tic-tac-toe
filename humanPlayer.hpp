#include "player.hpp"

class Human : public Player
{
    virtual std::pair<int, int> play(Board board, char piece);

    virtual void announceIWon(char piece);
};