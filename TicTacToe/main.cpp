#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "Board.h"

using namespace std;

struct TreeNode{
    Board state;
    vector<TreeNode*> childNodes;
};


class AI{
    public:
        AI();
        AI(Board* theBoard, bool AIside);
        int RandomMove(Board game);
        int AIMove();
        void FillPossibleMoves(Board& game);

        int MiniMax(Board& game, vector<int> remainMoves, bool maximizingPlayer);
        //int OMin(Board& game);
        int Value(Board evaluatedBoard);
        int Value(Board evaluatedBoard, int aMove);
    private:
        vector<int> possibleMoves;
        Board* boardPtr;
        bool side; //X == 1, O == 0
        int counter;
        TreeNode miniMaxTree;
};
AI::AI(){
    possibleMoves.clear();
}
AI::AI(Board* theBoard, bool AIside){
    possibleMoves.clear();
    boardPtr = theBoard;
    side = AIside;
    counter = 0;
}

int AI::RandomMove(Board game){
    int rMove;
    srand(time(NULL));
    rMove = (rand() % game.possibleMoves.size() );
    return game.possibleMoves.at(rMove);
}

int AI::AIMove(){
    int theMove = 1;
    Board game = *boardPtr;
    FillPossibleMoves(game);
    //vector<int> emptyVec;
    //emptyVec.clear();
    theMove = RandomMove(game);

   /* switch(counter){
        case 0:
            theMove = 2;
            break;
        case 1:
            theMove = 4;
            break;
        case 2:
            theMove = 5;
            break;
        default:
            theMove = RandomMove(game);
            break;
    }*/
    if(counter == 0){
        if(game.GetSquare(1,1) == ' '){
            counter++;
            return 5;
        }
        else{
            counter++;
            return 1;
        }
    }
    counter++;




    cout << "Thinking..." << endl;
    /*if(side){
        theMove = XMax(game);
    } else{
        theMove = OMin(game);
    }*/
    cout << "MiniMax returns: " << MiniMax(game, game.possibleMoves, game.GetTurn()) << endl;

    //PrintMiniMaxTree(*boardPtr, possibleMoves);

    return theMove;
}

int AI::MiniMax(Board& game, vector<int> remainMoves, bool maximizingPlayer){
    int bestValue;
    int tmpMove;
    int tmpValue;
    Board tmpGame;

    if(remainMoves.size() == 0 && game.CheckWin() != 0){ //Base Case: Tree fully searched -- No more moves possible
        cout << "Tree Searched. Result: " << game.CheckWin() << endl << endl;
        bestValue = Value(game);
        return bestValue;
    }
    else if(maximizingPlayer){
        bestValue = -1;
        for(int m = 0; m < remainMoves.size(); m++){
            if(game.CheckWin() == 0){
                tmpMove = remainMoves.at(m);
                tmpGame = game;
                game.VirtualMove(remainMoves.at(m));
                //moveCount++;
                remainMoves.erase(remainMoves.begin() + m);

                tmpValue = MiniMax(game, remainMoves, !maximizingPlayer);

                if(tmpValue > bestValue){
                    bestValue = tmpValue;
                }

                tmpValue = MiniMax(game, remainMoves, !maximizingPlayer);

                remainMoves.insert(remainMoves.begin() + m, tmpMove);
                game = tmpGame;
                return bestValue;
            } else{
                cout << "Result: "<< game.CheckWin() << endl << endl;
                bestValue = Value(game);
                return bestValue;
            }

        }
    }
    else{ //Recursion Case
        bestValue = 101;
        for(int m = 0; m < remainMoves.size(); m++){
            if(game.CheckWin() == 0){

                tmpMove = remainMoves.at(m);
                tmpGame = game;
                game.VirtualMove(remainMoves.at(m));
                //moveCount++;
                remainMoves.erase(remainMoves.begin() + m);

                tmpValue = MiniMax(game, remainMoves, !maximizingPlayer);

                if(tmpValue < bestValue){
                    bestValue = tmpValue;
                }
                remainMoves.insert(remainMoves.begin() + m, tmpMove);
                game = tmpGame;
                return bestValue;
            } else{
                cout << "Result: "<< game.CheckWin() << endl << endl;
                bestValue = Value(game);
                return bestValue;
            }
        }

    }

}
/**
function minimax(node, depth, maximizingPlayer)
    if depth = 0 or node is a terminal node
        return the heuristic value of node
    if maximizingPlayer
        bestValue := -infinity
        for each child of node
            val := minimax(child, depth - 1, FALSE)
            bestValue := max(bestValue, val)
        return bestValue
    else
        bestValue := +infinity
        for each child of node
            val := minimax(child, depth - 1, TRUE)
            bestValue := min(bestValue, val)
        return bestValue
*/

/*int AI::OMin(Board& game){
    int bestMove = 1;
    cout << "OMin initialized." << endl;
    FillPossibleMoves(game);
    for(int m = 0; m < possibleMoves.size(); m++){
        game.Move(possibleMoves.at(m));
        if(game.CheckWin() == 0){
            game.Move(XMax(game));
            if(game.CheckWin() == 2 ){//Value(possibleMoves.at(m), game) < Value(bestMove, game)){
                cout << "New bestMove found. (OMin)" << endl;
                bestMove = possibleMoves.at(m);
                break;
            }
        }
        else{
            return possibleMoves.at(m);
        }
    }
    return bestMove;
}*/

int AI::Value(Board evaluatedBoard){
    if(evaluatedBoard.CheckWin() == 1){
        return 100;
    }
    else if(evaluatedBoard.CheckWin() == 2){
        return 0;
    }
    else if(evaluatedBoard.CheckWin() == 3){
        cout << "Tie found" << endl;
        return 50;
    }
    else {
        cout << "Move evaluated to 0" << endl;
        return -1;
    }
}

int AI::Value(Board evaluatedBoard, int aMove){
    evaluatedBoard.Move(aMove);
    if(evaluatedBoard.CheckWin() == 1){
        return 100;
    }
    else if(evaluatedBoard.CheckWin() == 2){
        return 0;
    }
    else if(evaluatedBoard.CheckWin() == 3){
        cout << "Tie found" << endl;
        return 50;
    }
    else {
        cout << "Move evaluated to 0" << endl;
        return -1;
    }
}

void AI::FillPossibleMoves(Board& game){
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


int main()
{
    Board currentBoard;
    currentBoard.PrintBoard();
    int square;
    bool player;
    char userSelection;

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "Choose X or O: (enter 'X' or 'O'): ";
    cin >> userSelection;

    if(userSelection == 'X' || userSelection == 'x'){
        player = true;
    } else if(userSelection == 'o' || userSelection == 'O'){
        player = false;
    } else {
        cerr << "Invalid choice.";
        return -1;
    }

    AI noobyAI(&currentBoard, !player);

    do{
        if(currentBoard.GetTurn() == player){
            if(player ){
                cout << "X: ";
                cin >> square;
                if(square == 10){
                    currentBoard.PrintMiniMaxTree(currentBoard);
                }
                else{
                    currentBoard.Move(square);
                }
            }
            else{
                cout << "O: ";
                cin >> square;
                if(square == 10){
                    currentBoard.PrintMiniMaxTree(currentBoard);
                }
                else{
                    currentBoard.Move(square);
                }
            }
        } else{
            cout << "AI: " << endl;
            currentBoard.Move(noobyAI.AIMove());

        }



        if(currentBoard.CheckWin() == 1){
            cout << "X wins!" << endl;
             break;
        }
        else if(currentBoard.CheckWin() == 2){
            cout << "O wins!" << endl;
             break;
        }
        else if(currentBoard.CheckWin() == 3){
            cout << "Tie -- Board full" << endl;
             break;
        }



    }while(square != 'q');


    return 0;
}

//Move Functions Below
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

    turn = !turn;

    PrintBoard();

    return;
}

void Board::VirtualMove(int square){ //Same as regular move, but doesn't print board
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

    turn = !turn;
    cout << "Virtual move success!" << endl;
    return;
}
