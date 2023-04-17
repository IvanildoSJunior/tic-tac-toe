#include <vector>

class Board
{
    private:
        std::vector<char> board;
    public:
        Board(int dimension): board(dimension * dimension,EMPTY){}
}

