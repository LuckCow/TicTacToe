/* CSCI 261, Section A 
 * Homework 11: Magic Item Class
 * Author: Nick Collins
 *
 * 
 *
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "Board.h"

using namespace std;





int main()
{
    Board aBoard;
    char userIn;
    while(1){
        cout << "Do you want to play a game of Tic-Tac-Toe? (y = yes, n = no, s = stats" << endl;
        cin >> userIn;
        if(userIn == 'y'){
            aBoard.PlayGame();
        } else if(userIn == 's') {
            cout << "Wins: " << aBoard.GetWins()
                 << ", Losses: " << aBoard.GetLosses()
                 << ", Ties: " << aBoard.GetTies() << endl;
        }
        else if(userIn == 'n') {
            cout << "Goodbye!" << endl;
            break;
        }
        else{
            cout << "Invalid input, try again." << endl;
        }
    
    }
    
    return 0;
}
