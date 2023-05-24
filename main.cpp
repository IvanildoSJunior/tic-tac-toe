// Tic - Tac 0 Toe 2.0
//Plays the game of tic-tac-toe against a human opponent
//Uses pointers instead of refernces for function parameters

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "board.hpp"
#include <utility>
#include "player.hpp"
#include <memory>
#include "humanPlayer.hpp"
#include "machinePlayer.hpp"
#include "game.hpp"

// global constants
const char TIE = 'T';
const char NO_ONE = 'N';

//function prototypes
void instructions();
char askYesNo(std::string question);
Board::Position askPosition(std::string question);
std::pair<std::unique_ptr<Player>,std::unique_ptr<Player>> humanPiece();
char opponent(char piece);
void displayBoard(const std::vector<char>* const pBoard);
char winner(const std::vector<char>* const pBoard);
bool isLegal(const std::vector<char>* const pBoard, int move);
int humanMove(const std::vector<char>* const pBoard);
int computerMove(Board board, char piece);
void announceWinner(char winner, char computer, char human);

//main function
int main()
{
    Board board(dimension);
    instructions();
    std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> players = humanPiece();
    Game game(board, std::move(players.first), std::move(players.second));
    game.displayBoard();

    while (!game.isEnd())
    {
        game.playTurn();
        game.displayBoard();
    }
    game.announceWinner();

    return 0;
}

//functions

void instructions()
{
    std::cout << "Welcome to the ultimate man=machine showdown: Tic-Tac-Toe.\n";
    std::cout << "--where human brain is pit against silicon processor\n\n";

    std::cout << "Make your move known by entering a number, 0 - 8. The number\n";
    std::cout << "corresponds to the desired board position, as illustrated:\n\n";

    std::cout << "        0 | 1 | 2\n";
    std::cout << "        ---------\n";
    std::cout << "        3 | 4 | 5\n";
    std::cout << "        ---------\n";
    std::cout << "        6 | 7 | 8\n\n";

    std::cout << "Prepare yourself, human, The battle is about to begin. \n\n";
}

char askYesNo(std::string question)
{
    char response;
    do
    {
        std::cout << question << "(y/n): ";
        std::cin >> response;
    }while (response != 'y' && response != 'n');

    return response;
}

Board::Position askPosition(std::string question)
{
    int number;
    do
    {
        std::cout << question;
        std::cin >> number;
    }while (number > -1 || number < dimension * dimension);
    Board::Position position = new Board::Position(number / dimension, number % dimension)

    return position;
}

std::pair<std::unique_ptr<Player>, std::unique_ptr<Player> > humanPiece()
{
    char go_first = askYesNo("Do you require the fist move?");
    if (go_first == 'y')
    {
        std::cout << "\nThen take the first move. You will need it. \n";
        return std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>>(new Human(), new Machine());
    }
    else
    {
        std::cout << "\nYour bravery will be your undoing... I will go first.\n";
        return std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>>(new Machine(), new Human());
    }
}

char opponent(char piece)
{
    if (piece == X)
    {
        return O;
    }
    else
    {
        return X;
    }
}

void displayBoard(const std::vector<char>* const pBoard)
{
    std::cout << "\n\t" << (*pBoard)[0] << " | " << (*pBoard) [1] << " | " << (*pBoard) [2];
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << (*pBoard)[3] << " | " << (*pBoard) [4] << " | " << (*pBoard) [5];
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << (*pBoard)[6] << " | " << (*pBoard) [7] << " | " << (*pBoard) [8];
    std::cout << "\n\n";
}

char winner(const std::vector<char>* const pBoard)
{
    //all possible winning rows
    const int WINNING_ROWS[8][3] = { {0, 1, 2},
                                     {3, 4, 5},
                                     {6, 7, 8},
                                     {0, 3, 6},
                                     {1, 4, 7},
                                     {2, 5, 8},
                                     {0, 4, 8},
                                     {2, 4, 6} };
    const int TOTAL_ROWS = 8;

    //if any winning row has three values that are the same (and not EMPTY),
    //the we have a winner
    for(int row = 0; row < TOTAL_ROWS; ++row)
    {
        if ( ((*pBoard)[WINNING_ROWS[row][0]] != EMPTY) &&
             ((*pBoard)[WINNING_ROWS[row][0]] == (*pBoard)[WINNING_ROWS[row][1]]) &&
             ((*pBoard)[WINNING_ROWS[row][1]] == (*pBoard)[WINNING_ROWS[row][2]]) )
        {
            return (*pBoard)[WINNING_ROWS[row][0]];
        }
    }

    //since nobody has won, check for a tie (no empty squares left)
    if (count(pBoard->begin(), pBoard->end(), EMPTY) == 0)
    return TIE;

    //since nobody has won and it isn't a tie, the game ain't over
    return NO_ONE;
}

Board::Position humanMove(Board board, char piece)
{
    Board::Position position = askPosition("Where will you move?");
    while (!position.isLegal(board))
    {
        std::cout << "\nThat square is already occupied, foolish human.\n";
        position = askPosition("Where will you move?");
    }
    std::cout << "Fine...\n";
    return position;
}

Board::Position computerMove(Board board, char piece)
{
    unsigned int move = 0;
    bool found = false;

    //if piece can win on next move, thats the move to make
    for(Board::Position position:board)
    {
        if (found) break;

        if (position.isLegal(board))
        {
            //try move
            board[move] = piece;
            //test for winner
            found = board.winner() == piece;
            //undo move
            board[move] = EMPTY;
        }
    }
    
    //otherwise, if opponent can win onnext move, that's the move to make
    if (!found)
    {
        move = 0;
        char human = opponent(piece);

        for(Board::Position position:board)
        {
            if (position.isLegal(board))
            {
                //try move
                board[move] = human;
                //test for winner
                found = board.winner == human;
                //undo move
                board[move] = EMPTY;
            }

            if (!found)
            {
                ++move;
            }
        }
    }
    //otherwise, moving to the best open square is the move to make
    if (!found)
    {
        move = 0;
        unsigned int i = 0;

        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5 ,7};
        //pick best open square
        for(Board::Position position:board)
        {
            move = BEST_MOVES[i];
            if (position.isLegal(board))
            {
                found = true;
            }
            i++;
        }

    }
    std::cout << "I shall take square number " << move << std::endl;
    return move;
}


