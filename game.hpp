#include "board.hpp"
#include <memory>
#include "player.hpp"


class Game
{
    private:
        Board board;
        std::unique_ptr<Player> player_1;
        std::unique_ptr<Player> player_2;
        char turn;
    public:
    Game(Board board, std::unique_ptr<Player> p1, std::unique_ptr<Player> p2): board(board), turn(X)
    {
        player_1 = p1;
        player_2 = p2;
    };
};

