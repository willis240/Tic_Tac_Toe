// main.cpp
// William Fisher
// Jan. 26, 2021

//TODO: Win Conditions

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;
using std::istringstream;

void placeMarker(int slot, vector<int> & board)
{
	if (board[slot] == 2)
		cout << "o";
	else if (board[slot] == 1)
		cout << "x";
	else
		cout << " ";
}

void drawBoard(vector<int> & board)
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
					placeMarker(slot, board);
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

void playerTurn(int playerNum, vector<int> & board)
{
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

bool getResult(const vector<int>& check)
{
	if (std::equal(check.begin() + 1, check.end() - 1, check.begin()) || std::equal(check.begin() + 2, check.end(), check.begin() + 1))
	{
		if (check[1] == 1)
		{
			cout << "Player 1 wins!" << endl;
			return true;
		}
		else if (check[1] == 2)
		{
			cout << "Player 2 wins!" << endl;
			return true;
		}
	}
	return false;
}

bool winCheck(vector<int> & board)
{
	vector<int> check(5);

	//Horizontal Check
	int ii = 0;
	for (int i = 0; i < 25; i++)
	{
		if(i / 5 == ii)
			check[i % 5] = board[i];
		if (i % 5 == 4)
		{
			if (getResult(check))
				return true;
			ii++;
		}
	}
	return false;
}

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