/* CSCI 261, Section A
 * Homework 11: Magic Item Class
 * Author: Nick Collins
 *
 * Board.h Header File
 *
 * Description: Console Tic-Tac-Toe game that keeps track of the user's stats
 * User can select X or O side
 * Includes Reset, Quit, and Help functions
 * AI is somewhat smart, but not impossible
 */

#pragma once
#include <vector>


class Board{
public:
    Board(); //Constructor
    
    void PlayGame(); //Use this function to start a game, Everything about the game is handled privately
    
    //Getters
    int GetWins();
    int GetTies();
    int GetLosses();
    
private:
    //Variables
    std::vector<int> possibleMoves; //used for selecting a random move
    char board[3][3]; //The TicTacToe board ('X', 'O', and ' ')
    const int REF_BOARD[3][3] = {{1,2,3},{4,5,6},{7,8,9}}; //Refenence Board, converts [row][col] to 1-9 int
    bool turn; // True for X, false for O
    int moveCounter; //Counts moves made by AI
    int wins; //Stores amount of times human player won
    int losses; //Stores amount of times human player lost
    int ties; //Stores amount of times human player tied
    char lines[8][3]; //used in AI decision making
    int referenceLines[8][3]; //used to convert lines[][] back to 1-9 move
    bool player; //Human player's side -- True for X, False for O
    
    void Move(int square); //1 is X, 0 is O
    bool GetTurn();
    char GetSquare(int r, int c);
    int CheckWin(); //returns 0 for no winner, 1 for X, 2 for O
    
    //Private Functions
    void ResetGame(); //resets board
    void PrintBoard(); //Prints current board to console
    void Help(); //Prints commands and reference board
    void EndGame(); //Outputs end game results and resets board
    void FillPossibleMoves(); //fills possibleMoves vector
    void FillLines(); //fills lines[][] array
    void PrintLines(); //Prints lines[][] array (for debugging)
    int FindMove(); //AI move selection
    char CheckLine(int row);
    int GetSquareFromRow(int row);
    int RandomMove(); //used when AI cannot find good move
    int AIMove(); //Ai move selection
    void FillRefLines(); //fills referencelines[][] array (only used once for setup)
    void PrintRefBoard();
    
};

