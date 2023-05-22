#include "player.hpp"

class Machine : public Player
{
    virtual std::pair<int, int> play(Board board, char piece);

    virtual void announceIWon(char piece);
};