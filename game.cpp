#include<stdio.h>
#include<iostream>
#include "TTT.cpp"

using namespace std;

int main(){

    TTT game;
    int turn = 0;
    bool checkWinO = game.checkHasWon('O');
    bool checkWinX = game.checkHasWon('X');

    while( !checkWinO && !checkWinX ){
        char currentPlayer;
        cout << "AVAILABLE INPUTS - " << endl;
        game.printBoardStatus();
        game.printBoard();
        
        if((turn % 2) == 0){
            currentPlayer = 'O';
        } else {
            currentPlayer = 'X';
        }

        int position;
        bool validPosition = true;

        if(currentPlayer == 'O'){
            do{
                cout << "Chance of " << currentPlayer << ": ";
                scanf("%d", &position);
                int x = position / 3;
                int y = position % 3;

                validPosition = game.makeMove(currentPlayer, x, y);
                if(!validPosition){
                    cout << "INVALID POSITION" << endl;
                }
            } while(!validPosition);
        }
        else {
            cout << "CALLING AI" << endl;
            game.AI();
        }

        ++turn;
        checkWinO = game.checkHasWon('O');
        checkWinX = game.checkHasWon('X');

        if(turn == 9 && !checkWinO && !checkWinX){
            break;
        }
        
        // ADD CLEAR SCREEN CODE 
        cout << "\033[2J\033[1;1H";
    }

    game.printBoard();
    if(checkWinO) cout << "O WON!!!!" << endl;
    else if(checkWinX) cout << "X WON!!!!" << endl;
    else cout << "TIE..." << endl;

    return 0;
};