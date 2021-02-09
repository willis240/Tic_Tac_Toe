// main.cpp
// William Fisher
// Jan. 26, 2021

//TODO: make eval function (apply only to leafs) which prioritizes spaces in open centers, 
//add ability to save replays (save each change to board as it happens)

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;

int main()
{
	int turnCount = 1;
	int playerNum = 1;
	vector<char> board = {0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0};

	vector<int> movesMade;

	cout << "Welcome to Tic-Tac_Toe: 4-In-A-Row!" << endl << endl << "Choose a mode!" << endl << endl;
	cout << "1: player vs. player" << endl;
	cout << "2: player vs. bot" << endl;
	cout << "3: bot vs. bot" << endl;
	cout << "4: playback saved game" << endl;

	int choice = selectMode();

	while (true)
	{
		drawBoard(board);

		int result = winCheck(board);

		if (result == 1)
		{
			cout << "Player 1 wins!" << endl;
			break;
		}
		if (result == 2)
		{
			cout << "Player 2 wins!" << endl;
			break;
		}
		if (result == 3)
		{
			cout << "No available spaces left. It is a draw." << endl;
			break;
		}

		turnOrder(playerNum, board, choice, turnCount, movesMade);
		turnCount++;
	}

	if (choice != 4)
		askForSave(movesMade);

}