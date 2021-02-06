// main.cpp
// William Fisher
// Jan. 26, 2021

//TODO: ability to save replays (save each change to board as it happens), make AI

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

	cout << "Welcome to Tic-Tac_Toe: 4-In-A-Row!" << endl << endl << "Choose a mode!" << endl << endl;
	cout << "1: player vs. player" << endl;
	cout << "2: player vs. bot" << endl;
	cout << "3: bot vs. bot" << endl;
	cout << "4: playback saved game" << endl;

	int choice = selectMode();

	while (true)
	{
		drawBoard(board);

		if (winCheck(board))
			break;

		/*if (choice == 3)
		{
			cout << "Press enter to continue..." << endl;
			std::getchar();
		}*/

		turnOrder(playerNum, board, choice, turnCount);
		turnCount++;
	}
}