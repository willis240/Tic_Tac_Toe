// main.cpp
// William Fisher
// Jan. 26, 2021

//TODO: Diagonal Win Conditions, Tie conditions, ability to save replays (save each change to board as it happens), make AI
//also add choice of pvp, pvbot, and botvbot

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;
using std::istringstream;

int main()
{
	int turnCount = 1;
	int playerNum = 1;
	vector<int> board = { 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0 };
	while (true)
	{
		drawBoard(board);

		if (winCheck(board))
			break;

		if (turnCount % 2 == 1)
			playerNum = 1;
		else
			playerNum = 2;

		cout << endl << "It is Player " << playerNum << "'s turn! Pick an " << endl;
		cout << "available space between 1 and 25!" << endl;
		playerTurn(playerNum, board);
		turnCount++;
	}
}