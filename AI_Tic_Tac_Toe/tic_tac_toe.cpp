// tic_tac_toe.cpp
// William Fisher
// Feb. 4, 2021

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;
using std::istringstream;

int selectMode()
{
	while (true)
	{
		int input;
		std::cin >> input;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input. Please input the number of the mode you'd like to select." << endl;
		}
		else if (input > 0 && input < 5)
			return input;
		else
			cout << "That number does not correspond to any of the available modes. Please try again." << endl;
	}
}

void placeMarker(int slot, vector<char>& board)
{
	if (board[slot] == 2)
		cout << "o";
	else if (board[slot] == 1)
		cout << "x";
	else
		cout << " ";
}

void drawBoard(vector<char>& board)
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

void playerTurn(int playerNum, vector<char>& board)
{
	cout << endl << "It is Player " << playerNum << "'s turn! Pick an " << endl;
	cout << "available space between 1 and 25!" << endl;

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
		else if (input > 0 && input < board.size() + 1)
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
			cout << "That number does not work. Please select a vacant space between 1 and 25." << endl;
	}
}

void playbackTurn(int playerNum, vector<char>& board)
{
	cout << "Hey man! I'm a dummy in playbackTurn!" << endl;
}

int getResult(const vector<char>& check)
{
	if (std::equal(check.begin() + 1, check.end() - 1, check.begin()) || std::equal(check.begin() + 2, check.end(), check.begin() + 1))
	{
		if (check[1] == 1)
			return 1;
		if (check[1] == 2)
			return 2;
	}
	return 0;
}

bool tieCheck(vector<char>& board)
{
	if (std::find(board.begin(), board.end(), 0) == board.end())
		return true;

	return false;
}

int winCheck(vector<char>& board)
{
	vector<char> check(5);
	int ii = 0;

	//Horizontal Check
	for (int i = 0; i < 25; i++)
	{
		if (i / 5 == ii)
			check[i % 5] = board[i];
		if (i % 5 == 4)
		{
			char result = getResult(check);
			if (result == 1)
				return 1;
			if (result == 2)
				return 2;
			ii++;
		}
	}

	//Vertical Check
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 25; i++)
		{
			if (i % 5 == j)
				check[i / 5] = board[i];
			if (i / 5 == 4)
			{
				char result = getResult(check);
				if (result == 1)
					return 1;
				if (result == 2)
					return 2;
			}
		}
	}

	//Diagonal Check
	int modResult = 0;
	int moddedNum = 6;
	int beginNum = 0;
	int endNum = 25;
	for (int j = 0; j < 6; j++)
	{
		for (int i = beginNum; i < endNum; i++)
		{
			if (i % moddedNum == modResult)
			{
				if (moddedNum == 6)
					check[i / moddedNum] = board[i];
				else
					check[(i - 2) / moddedNum] = board[i];
			}
			if (i == (endNum - 1))
			{
				char result = getResult(check);
				if (result == 1)
					return 1;
				if (result == 2)
					return 2;
			}
		}

		if (j == 0)
			modResult = 1;
		if (j == 1)
			modResult = 5;
		if (j == 2)
		{
			modResult = 0;
			moddedNum = 4;
			beginNum = 4;
			endNum = 21;
		}
		if (j == 3)
		{
			check[0] = 0;
			modResult = 1;
			beginNum = 9;
			endNum = 22;
		}
		if (j == 4)
		{
			modResult = 3;
			beginNum = 3;
			endNum = 16;
		}
		if (modResult != 0)
			check[4] = 0;
	}

	if (tieCheck(board))
		return 3;

	return 0;
}

void turnOrder(int& playerNum, vector<char>& board, const int & choice, const int& turnCount)
{
	if (turnCount % 2 == 1)
	{
		playerNum = 1;
		if (choice == 2)
			playerTurn(playerNum, board);
	}
	else 
	{
		playerNum = 2;
		if (choice == 2)
			botTurn(playerNum, board);
	}

	if (choice == 1)
		playerTurn(playerNum, board);
	if (choice == 3)
	{
		botTurn(playerNum, board);
		cout << "Press enter to continue..." << endl;
		std::getchar();
	}
	if (choice == 4)
		playbackTurn(playerNum, board);
}