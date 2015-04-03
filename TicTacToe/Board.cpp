#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            board[r][c] = ' ';
        }
    }
    turn = 1;
    possibleMoves.clear();
    FillPossibleMoves(*this);
    moveCount = 0;
}

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

bool Board::GetTurn(){
    return turn;
}

char Board::GetSquare(int r, int c){
    return board[r][c];
}

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

void Board::PrintMiniMaxTree(Board game){
    FillPossibleMoves(game);
    vector<int> remainMoves = game.possibleMoves;

    cout << "---Generating MiniMax Tree---" << endl;
    MiniMaxTree(game, remainMoves);
    cout << "---MiniMax Tree Complete---" << endl;
    cout << "Move count: " << moveCount << endl;
    return;
}

void Board::MiniMaxTree(Board game, vector<int> remainMoves){
    int tmpMove;
    Board tmpGame;

    if(remainMoves.size() == 0 && game.CheckWin() != 0){ //Base Case: Tree fully searched -- No more moves possible
        cout << "Tree Searched. Result: " << game.CheckWin() << endl << endl;
    }
    else{ //Recursion Case
        for(int m = 0; m < remainMoves.size(); m++){
            if(game.CheckWin() == 0){
                tmpMove = remainMoves.at(m);
                tmpGame = game;
                game.Move(remainMoves.at(m));
                moveCount++;
                remainMoves.erase(remainMoves.begin() + m);

                MiniMaxTree(game, remainMoves);

                remainMoves.insert(remainMoves.begin() + m, tmpMove);
                game = tmpGame;
            } else{
                cout << "Result: "<< game.CheckWin() << endl << endl;
            }
        }
    }
    return;
}


void Board::FillPossibleMoves(Board& game){
    game.possibleMoves.clear();
    if(game.CheckWin() == 0){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            if(game.GetSquare(r,c) == ' '){
                if(r == 0){
                    game.possibleMoves.push_back(c+1);
                }
                else if(r == 1){
                    game.possibleMoves.push_back(c+4);
                }
                else if(r == 2){
                    game.possibleMoves.push_back(c+7);
                }
            }
        }
    }
    }
    return;
}
