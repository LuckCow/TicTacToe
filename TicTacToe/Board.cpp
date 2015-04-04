/* CSCI 261, Section A
 * Homework 11: Magic Item Class
 * Author: Nick Collins
 *
 * Board.cpp Implementation File
 *
 * Description: Console Tic-Tac-Toe game that keeps track of the user's stats
 * User can select X or O side
 * Includes Reset, Quit, and Help functions
 * AI is somewhat smart, but not impossible
 */

#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Constructor
Board::Board(){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            board[r][c] = ' ';
        }
    }
    turn = 1;
    possibleMoves.clear();
    FillPossibleMoves();
    moveCounter = 0;
    wins = 0;
    losses = 0;
    ties = 0;
    FillLines();
    FillRefLines();
}

//Reset: resets all data except statistics tracker and player
void Board::ResetGame(){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            board[r][c] = ' ';
        }
    }
    turn = 1;
    possibleMoves.clear();
    FillPossibleMoves();
    moveCounter = 0;
    FillLines();
    return;
}

void Board::PlayGame(){
    int userInput;
    char userSelection;
    bool isContinuing = true;
    
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "Enter 0 for help, or -1 to quit, -2 to reset" << endl;
    cout << "Move by inputting a number between 1 and 9" << endl;
    cout << "Choose X or O: (enter 'X' or 'O'): ";
    cin >> userSelection;
    
    if(userSelection == 'X' || userSelection == 'x'){
        player = true;
    } else if(userSelection == 'o' || userSelection == 'O'){
        player = false;
    } else {
        cerr << "Invalid choice. Ending Game." << endl;
        return;
    }
    
    PrintBoard();
    
    while(isContinuing){
        if(GetTurn() == player){
            if(player ){
                cout << "X: ";
            }
            else{
                cout << "O: ";
            }

            cin >> userInput;
            
            if(userInput >= 1 && userInput <= 9){
                Move(userInput);
            }
            else if(userInput == 0){
                Help();
            }
            else if(userInput == -1){
                EndGame();
                isContinuing = false;
            }
            else if(userInput == -2){
                cout << "Resetting Game..." << endl;
                ResetGame();
                PrintBoard();
                continue;
            }
            
        }
    else{
            cout << "AI: " << endl;
            Move(AIMove());
            
        }
        
        if(CheckWin() != 0){
            EndGame(); //Outputs end game result and increments player statistics counters
            isContinuing = false;
            break;
        }
        
        
    }
    

    return;
}

//Prints Rules, Commands, and Reference Board
void Board::Help(){
    cout << "Rules: X goes First" << endl;
    cout << "3 in a row, column, or diagonal wins" << endl;
    cout << "It is a tie if the board is filled and no moves are left." << endl;
    cout << "Enter 0 for help, or -1 to quit, -2 to reset" << endl;
    cout << "Move by inputting a number between 1 and 9" << endl;
    PrintRefBoard();
    return;
}

//Outputs end game result and increments player statistics counters
void Board::EndGame(){
    //If game if quit in the middle
    if(CheckWin() == 0){
        cout << "Quiting game." << endl;
    }
    //If X wins
    else if(CheckWin() == 1){
        if(player){
            cout << "Congratulations, X wins!" << endl;
            wins++;
        }
        else{
            cout << "Sorry, You Lose." << endl;
            losses++;
        }
    }
    
    //If O wins
    else if(CheckWin() == 2){
        if(!player){
            cout << "Congratulations, O wins!" << endl;
            wins++;
        }
        else{
            cout << "Sorry, you lost." << endl;
            losses++;
        }
    }
    
    //If game ends in tie
    else if(CheckWin() == 3){
        cout << "Tie -- Board full" << endl;
        ties++;
    }
    
    ResetGame(); //Reset game
    return;
}

//Prints Board to screen
void Board::PrintBoard(){
    cout << endl;
    for(int r = 0; r < 3; r++){
        cout << "  ";
        for(int c = 0; c < 3; c++){
            cout << board[r][c];
            if(c < 2){
                cout << " | ";
            }
        }
        cout << endl;
        if(r < 2){
            cout << "  ---------";
            cout << endl;
        }
    }
    return;
}

int Board::GetWins(){
    return wins;
}
int Board::GetTies(){
    return ties;
}
int Board::GetLosses(){
    return losses;
}

bool Board::GetTurn(){
    return turn;
}

char Board::GetSquare(int r, int c){
    return board[r][c];
}

//Checks current board for a win
int Board::CheckWin(){//returns 0 for no winner, 1 for X, 2 for O, 3 for tie
    
    //Check Vertical
    for(int col = 0; col < 3; col ++){
        if( (board[0][col] == board[1][col]) && (board[1][col] == board[2][col])){
            if(board[0][col] == 'X'){
                return 1;
            }
            else if(board[0][col] == 'O'){
                return 2;
            }
        }
    }
    
    //Check Horizonal
    for(int row = 0; row < 3; row ++){
        if( (board[row][0] == board[row][1]) && (board[row][1] == board[row][2])){
            if(board[row][0] == 'X'){
                return 1;
            }
            else if(board[row][0] == 'O'){
                return 2;
            }
        }
    }
    
    //For diagonal
    if( (board[0][0] == board[1][1]) && (board[1][1] == board[2][2])){
        if(board[0][0] == 'X'){
            return 1;
        }
        else if(board[0][0] == 'O'){
            return 2;
        }
    }
    
    if( (board[0][2] == board[1][1]) && (board[1][1] == board[2][0])){
        if(board[0][2] == 'X'){
            return 1;
        }
        else if(board[0][2] == 'O'){
            return 2;
        }
    }
    
    
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            if(board[r][c] == ' '){
                return 0;
            }
        }
    }
    
    
    return 3;
}

//Populates possibleMoves vector
void Board::FillPossibleMoves(){
    possibleMoves.clear();
    if(CheckWin() == 0){
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(GetSquare(r,c) == ' '){
                    if(r == 0){
                        possibleMoves.push_back(c+1);
                    }
                    else if(r == 1){
                        possibleMoves.push_back(c+4);
                    }
                    else if(r == 2){
                        possibleMoves.push_back(c+7);
                    }
                }
            }
        }
    }
    return;
}

void Board::FillLines(){
    /* Fills the lines[8][3] array
     each row holds a '3-in-a-row' possible win
     rows 0-2 are horizontal 'rows'
     rows 3-5 are verticle 'rows'
     rows 6 and 7 are diagonals   */
    
    //horizonal lines
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            lines[r][c] = board[r][c];
        }
    }
    //Vertical Lines
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            lines[r+3][c] = board[c][r];
        }
    }
    
    //Top-Bottom Diagonal
    lines[6][0] = board[0][0];
    lines[6][1] = board[1][1];
    lines[6][2] = board[2][2];
    
    //Bottom Top Diagonal
    lines[7][0] = board[0][2];
    lines[7][1] = board[1][1];
    lines[7][2] = board[2][0];
    return;
}

//Returns the blank square number from the row of the lines[][] array
int Board::GetSquareFromRow(int row){
    int blankColumn = 0;
    for(int c = 0; c < 3; c++){
        if(lines[row][c] == ' '){
            blankColumn = c;
        }
    }
    return referenceLines[row][blankColumn];
}

//Picks random move from using indexes of possible move vector
int Board::RandomMove(){
    int rMove;
    srand(time(NULL));
    rMove = (rand() % possibleMoves.size() );
    return possibleMoves.at(rMove);
}

int Board::AIMove(){
    int theMove = 0;
    FillPossibleMoves();
    FillLines();
    
    //Sets move to what the FindMove
    theMove = FindMove();
    
    //Takes middle on turn 1, or top left if that is taken
    if(moveCounter == 0){
        if(GetSquare(1,1) == ' '){
            moveCounter++;
            return 5;
        }
        else{
            moveCounter++;
            return 1;
        }
    }
    
    //if FindMove did not find anything (returned 0), a random move is selected
    if(theMove == 0){ 
        //cout << "Random move selected" ; //For debugging
        theMove = RandomMove();
    }
    
    moveCounter++;
    
    return theMove;
}

//Selects the AI's move by looking at all of the 'lines' in the lines[][] array
int Board::FindMove(){ 
    int theMove = 0;
    char AIside = 'X';
    char humanSide = 'O';
    if(player){
        AIside = 'O';
        humanSide = 'X';
    }
    for(int row = 0; row < 8; row++){
        if(CheckLine(row) == AIside){
            //If there is a possible win for the side that the AI is playing,
            //It stops checking the rows and picks this move
            theMove = GetSquareFromRow(row);
            break;
        }
        else if(CheckLine(row) == humanSide){
            //If there is a move that the opponent could win with, the AI will pick this move to block
            theMove = GetSquareFromRow(row);
        }
    }
    //cout << "FindMove selected theMove: " << theMove << endl; //For debugging
    return theMove;
}

//Checks a single row of the lines[][] array for possible wins (2 of X/O and a blank spot)
char Board::CheckLine(int row){
    char possibleWin = ' ';
    int xCount = 0;
    int oCount = 0;
    int blankCount = 0;
    for(int i = 0; i < 3; i++){
        if(lines[row][i] == 'X'){
            xCount++;
        }
        else if(lines[row][i] == 'O'){
            oCount++;
        }
        else if(lines[row][i] == ' '){
            blankCount++;
        }
    }
    if(xCount == 2 && blankCount == 1){
        //cout << "Possible X win" << endl; //for debuggins
        possibleWin = 'X';
    }
    else if(oCount == 2 && blankCount == 1){
        possibleWin = 'O';
    }
    return possibleWin;
}

//Move Function: Places X or O depending on turn, checks if square is taken, switches turn
void Board::Move(int square){
    char XO;
    if(turn){
        XO = 'X';
    }
    else{
        XO = 'O';
    }
    
    if(square > 10 || square < 1){
        cerr << "Invalid move range" << endl;
        return;
    }
    
    switch(square){
        case 1:
            if(board[0][0] == ' '){
                board[0][0] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 2:
            if(board[0][1] == ' '){
                board[0][1] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 3:
            if(board[0][2] == ' '){
                board[0][2] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 4:
            if(board[1][0] == ' '){
                board[1][0] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 5:
            if(board[1][1] == ' '){
                board[1][1] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 6:
            if(board[1][2] == ' '){
                board[1][2] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 7:
            if(board[2][0] == ' '){
                board[2][0] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 8:
            if(board[2][1] == ' '){
                board[2][1] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        case 9:
            if(board[2][2] == ' '){
                board[2][2] = XO;
            }
            else{
                cerr << "Square Taken." << endl;
                return;
            }
            break;
        default:
            cout << "Invalid Move." << endl;
            return;
            break;
    }
    
    turn = !turn; //Switches turn
    
    PrintBoard(); //Prints board
    
    return;
}

//This function is used to fill the referenceLines
void Board::FillRefLines(){
    //horizonal lines
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            referenceLines[r][c] = REF_BOARD[r][c];
        }
    }
    //Vertical Lines
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            referenceLines[r+3][c] = REF_BOARD[c][r];
        }
    }
    
    //Top-Bottom Diagonal
    referenceLines[6][0] = REF_BOARD[0][0];
    referenceLines[6][1] = REF_BOARD[1][1];
    referenceLines[6][2] = REF_BOARD[2][2];
    
    //Bottom Top Diagonal
    referenceLines[7][0] = REF_BOARD[0][2];
    referenceLines[7][1] = REF_BOARD[1][1];
    referenceLines[7][2] = REF_BOARD[2][0];
    return;
}

//Same as PrintBoard, but with the Reference Board
void Board::PrintRefBoard(){
    cout << endl;
    cout << "Reference Board: " << endl;
    for(int r = 0; r < 3; r++){
        cout << "  ";
        for(int c = 0; c < 3; c++){
            cout << REF_BOARD[r][c];
            if(c < 2){
                cout << " | ";
            }
        }
        cout << endl;
        if(r < 2){
            cout << "  ---------";
            cout << endl;
        }
    }
    return;
}

// Prints the contents of lines[][] (used for debugging)
void Board::PrintLines(){
    cout << "Lines: " << endl;
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 3; c++){
            cout << lines[r][c] << ",  " ;
        }
        cout << endl;
    }
    cout << endl;
    return;
}

