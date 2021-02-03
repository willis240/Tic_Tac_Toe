// main.cpp
// William Fisher
// Jan. 26, 2021

//TODO: Implement Player Turns and rules, including Win Conditions

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;
using std::istringstream;

vector<int> board = { 1, 0, 2, 0, 0,
					  0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0,};

void placeMarker(int slot)
{
	if (board[slot] == 2)
		cout << "o";
	else if (board[slot] == 1)
		cout << "x";
	else
		cout << " ";
}

void drawBoard()
{
	int slot = 0;
	for (int height = 0; height < 10; height++)
	{
		for (int width = 0; width < 25; width++)
		{
			if (height != 0)
			{
				if (height % 2 == 0)
					cout << "-";
				else if (width % 5 == 3)
				{
					placeMarker(slot);
					slot++;
				}
				else if (width % 5 == 0 && width != 0)
					cout << "|";
				else
					cout << " ";
			}
		}
		cout << endl;
	}
}

void playerTurn(int playerNum)
{
	//take input from player
	//check that it is valid input
	//if it's valid, change that spot in board
	//to either x's or o's, depending on the playerNum
	while (true)
	{
		int input;
		std::cin >> input;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input. Please enter the number of a vacant space." << endl;
		}
		else if (input > 0 && input < 26)
		{
			if (board[input - 1] == 0)
			{
				if (playerNum == 1)
					board[input - 1] = 1;
				else
					board[input - 1] = 2;
				break;
			}
			else
				cout << "That space is already occupied. Please select a vacant space." << endl;
		}
		else
			cout << "That number is too large. Please select a vacant space between 1 and 25." << endl;
	}
}

int main()
{
	int turnCount = 1;
	int playerNum = 1;
	while (true)
	{
		drawBoard();

		if (turnCount % 2 == 1)
			playerNum = 1;
		else
			playerNum = 2;

		cout << endl << "It is Player " << playerNum << "'s turn! Pick an " << endl;
		cout << "available space between 1 and 25!" << endl;
		playerTurn(playerNum);
		turnCount++;
	}
}