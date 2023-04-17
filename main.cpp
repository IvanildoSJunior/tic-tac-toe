// Tic - Tac 0 Toe 2.0
//Plays the game of tic-tac-toe against a human opponent
//Uses pointers instead of refernces for function parameters

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "board.hpp"

// global constants
const char TIE = 'T';
const char NO_ONE = 'N';

//function prototypes
void instructions();
char askYesNo(std::string question);
int askNumber(std::string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const std::vector<char>* const pBoard);
char winner(const std::vector<char>* const pBoard);
bool isLegal(const std::vector<char>* const pBoard, int move);
int humanMove(const std::vector<char>* const pBoard);
int computerMove(std::vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

//main function
int main()
{
    int move;
    const int NUM_SQUARES = 9;
    std::vector<char> board(NUM_SQUARES, EMPTY);

    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(&board);

    while (winner(&board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(&board);
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(&board);
        turn = opponent(turn);
    }
    announceWinner(winner(&board), computer, human);

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

int askNumber(std::string question, int high, int low)
{
    int number;
    do
    {
        std::cout << question << " (" << low << " - " << high << "): ";
        std::cin >> number;
    }while (number > high || number < low);

    return number;
}

char humanPiece()
{
    char go_first = askYesNo("Do you require the fist move?");
    if (go_first == 'y')
    {
        std::cout << "\nThen take the first move. You will need it. \n";
        return X;
    }
    else
    {
        std::cout << "\nYour bravery will be your undoing... I will go first.\n";
        return O;
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

inline bool isLegal(int move, const std::vector<char>* pBoard)
{
    return ((*pBoard)[move] == EMPTY);
}
int humanMove(const std::vector<char>* const pBoard)
{
    int move = askNumber("Where will you move?",(pBoard->size() - 1));
    while (!isLegal(move, pBoard))
    {
        std::cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber("Where will you move?", (pBoard->size() - 1));
    }
    std::cout << "Fine...\n";
    return move;
}

int computerMove(std::vector<char> board, char computer)
{
    unsigned int move = 0;
    bool found = false;

    //if computer can win on next move, thats the move to make
    while (!found && move < board.size())
    {
        if (isLegal(move, &board))
        {
            //try move
            board[move] = computer;
            //test for winner
            found = winner(&board) == computer;
            //undo move
            board[move] = EMPTY;
        }

        if (!found)
        {
            ++move;
        }
    }

    //otherwise, if opponent can win onnext move, that's the move to make
    if (!found)
    {
        move = 0;
        char human = opponent(computer);

        while (!found && move < board.size())
        {
            if (isLegal(move, &board))
            {
                //try move
                board[move] = human;
                //test for winner
                found = winner(&board) == human;
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
        while (!found && i < board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(move, &board))
            {
                found = true;
            }
            i++;
        }

    }
    std::cout << "I shall take square number " << move << std::endl;
    return move;
}

void announceWinner(char winner, char computer, char human)
{
    if (winner == computer)
    {
        std::cout << winner << "'s won!\n";
        std::cout << "As I predicted, human, I am triumphant once more -- proof\n";
        std::cout << "that computers are superior to humans in all regards.\n";
    }
    else if (winner == human)
    {
        std::cout << winner << "'s won!\n";
        std::cout << "No, no! It cannot be!  Somehow you tricked me, human.\n";
        std::cout << "But never again! I, the computer, so swear it!\n";
    }
    else
    {
        std::cout << "It's a tie.\n";
        std::cout << "You were most lucky, human, and somehow managed to tie me.\n";
        std::cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
}

