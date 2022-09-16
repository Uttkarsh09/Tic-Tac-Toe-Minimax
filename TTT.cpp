#include<iostream>
#include<ctype.h>

using namespace std;

class TTT{
	int grid[3][3], winningPositions[8][3] = {
		{0, 1, 2},		// Horizontal row 1
		{3, 4, 5},		// Horizontal row 2
		{6, 7, 8},		// Horizontal row 3
		{0, 3, 6},		// Vertical row 1
		{1, 4, 7},		// Vertical row 2
		{2, 5, 8},		// Vertical row 3
		{0, 4, 8},		// Diagonal left to right
		{2, 4, 6}		// Diagonal right to left
	};

	public:
	
	TTT(){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				this->grid[i][j] = 0;
			}
		}
	}


	bool checkHasWon(char player){
		int targetPlayerNumber = (player == 'X') ? 1 : 2;

		for(int i=0 ; i<8 ; i++){
			int matchCount = 0;
			for(int j=0 ; j<3 ;j++){
				int x = this->winningPositions[i][j] / 3;
				int y = this->winningPositions[i][j] % 3;

				if(this->grid[x][y] == targetPlayerNumber){
					++matchCount;
				}
			}
			if(matchCount == 3) return true;
		}

		return false;
	}

	bool makeMove(char player, int x, int y){
		if(isPositionTaken(x, y)) return false;
		this->grid[x][y] = (player == 'X') ? 1 : 2;
		return true;
	}

	bool isPositionTaken(int x, int y){
		if((x<3) && (y<3) && (this->grid[x][y] == 0)) return false;
		return true;
	}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int miniMax(int newGrid[3][3], bool isMaximizing){
		bool winX = false;
		bool winO = false;

		// check winner X
		int targetPlayerNumber = 1;
		for(int i=0 ; i<8 ; i++){
			int matchCount = 0;
			for(int j=0 ; j<3 ;j++){
				int x = this->winningPositions[i][j] / 3;
				int y = this->winningPositions[i][j] % 3;

				if(newGrid[x][y] == targetPlayerNumber){
					++matchCount;
				}
			}
			if(matchCount == 3) {
				winX = true;
				break;
			}
			else winX = false;
		}

		// check winner Y?
		targetPlayerNumber = 2;
		for(int i=0 ; i<8 ; i++){
			int matchCount = 0;
			for(int j=0 ; j<3 ;j++){
				int x = this->winningPositions[i][j] / 3;
				int y = this->winningPositions[i][j] % 3;

				if(newGrid[x][y] == targetPlayerNumber){
					++matchCount;
				}
			}
			if(matchCount == 3){
				winO = true;
				break;
			}
			else winO = false;
		}
		
		// checking if tie
		bool isTie = true;
		for(int i=0;i<9;i++){
			int x = i / 3;
			int y = i % 3;
			if((newGrid[x][y] == 0)){
				isTie = false;
			}
		}

		if(winX){
			return 1;
		}
		else if(winO){
			return -1;
		}
		else if(isTie){
			return 0;
		}
		
		if(isMaximizing){
			int maxScore = -100;
			for(int i=0 ; i<9 ; i++){
			 	int x = i / 3;
				int y = i % 3;

				if(newGrid[x][y] == 0){
					newGrid[x][y] = 1;			// check player X
					int score = miniMax(newGrid, false);
					if(score > maxScore){
						maxScore = score;
					}
					newGrid[x][y] = 0;
				}
			}
			return maxScore;
		}
		else{
			// cout << "IN 2222222222222222222222222222222222" << endl;
			int minScore = 100;
			for(int i=0 ; i<9 ; i++){
				int x = i / 3;
				int y = i % 3;

				if(newGrid[x][y] == 0){
					newGrid[x][y] = 2;			// check player y
					int score = miniMax(newGrid, true);
					if(score < minScore){
						minScore = score;
					}
					newGrid[x][y] = 0;
				}	
			}
			return minScore;
		}
	}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	void AI(){
		int choice = -1;
		int bestMove = -1000;
		int localGrid[3][3];

		for(int i=0;i<=8;i++){
			int x = i / 3;
			int y = i % 3;
			localGrid[x][y] = this->grid[x][y];
		}

		for(int i=0 ; i<=8 ; i++){
			int x = i / 3;
			int y = i % 3;

			if(localGrid[x][y] == 0){
				localGrid[x][y] = 1;

				int move = miniMax(localGrid, false);
				if(bestMove < move){
					bestMove = move;
					choice = i;
				}
				localGrid[x][y] = 0;
			}
		}
		this->makeMove('X', choice/3, choice%3);
	}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	void printBoard(){
		for(int i=0 ; i<3 ; i++){
			for(int j=0 ; j<3 ; j++){
				int x = this->grid[i][j];
				
				cout << " ";
				if(x == 0){
					cout << " ";
				} 
				else if(x == 1){
					cout << "X";
				} 
				else {
					cout << "O";
				}
				cout << " ";
				if(j < 2) cout << "|";
			}
			
			cout << "\n";
			if(i!=2){
				cout << "-----------" << endl;
			}
		}
		cout << "\n";
	}

	void printBoardStatus(){
		for(int i=0 ; i<3 ; i++){
			for(int j=0 ; j<3 ; j++){
				int x = (i*3) + j;

				cout << " ";
				if(this->isPositionTaken(i, j)){
					cout << "\033[1;31m" << x << "\033[1;37m";
				}
				else {
					cout << "\033[1;32m" << x << "\033[1;37m";
				}
				cout << " ";

				if(j<2) cout << "|";
			}
			cout << "\n";
			if(i < 2) cout << "-----------\n";
		}
		cout << "\n";
	}
};