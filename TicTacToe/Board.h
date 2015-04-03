#ifndef BOARD_H
#define BOARD_H
#include <vector>


class Board{
    public:
        Board();

        void PrintBoard();
        void Move(int square); //1 is X, 0 is O
        void VirtualMove(int square);
        bool GetTurn();
        char GetSquare(int r, int c);
        int CheckWin(); //returns 0 for no winner, 1 for X, 2 for O

        void PrintMiniMaxTree(Board game);
        void MiniMaxTree(Board game, std::vector<int> remainMoves);
        void FillPossibleMoves(Board& game);

        std::vector<int> possibleMoves; //Public Var -- OOps
    private:
        char board[3][3];
        bool turn;
        int moveCount;

};


#endif // BOARD_H
