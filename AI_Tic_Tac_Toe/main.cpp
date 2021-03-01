// main.cpp
// William Fisher
// Jan. 26, 2021

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;

int main()
{
	while (true)
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
		cout << "5: quit" << endl;

		int choice = selectMode();

		char typeAIone;
		char typeAItwo;
		int timeForAI;
		if (choice == 3)
		{
			cout << "Please select the algorithm you would like the player 1 bot to utilize." << endl << endl;
			typeAIone = selectAI();
		}
		if (choice == 2 || choice == 3)
		{
			cout << "Please select the algorithm you would like the player 2 bot to utilize." << endl << endl;
			typeAItwo = selectAI();
			cout << "How many seconds would you like the bot(s) to have for their turns?" << endl << endl;
			timeForAI = selectTime();
		}
		
		if (choice == 5)
			break;

		vector<int> moves;
		if (choice == 4)
			moves = getMoveData();
	
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
			turnOrder(playerNum, board, choice, turnCount, movesMade, moves, typeAIone, typeAItwo, timeForAI);
			turnCount++;
		}

		if (choice != 4)
			askForSave(movesMade);
	}
}