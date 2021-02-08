// bot.cpp
// William Fisher
// Feb. 4, 2021

#include "header.hpp"
using std::cout;
using std::endl;
using std::vector;

int evalFunc(int & playerNum, vector<int> board)
{
	return 0;
}

int minimax(vector<int> & board, int depth, bool isMaximizingPlayer, int & playerNum)
{
	int score = std::numeric_limits<int>::max();
	int chosenMove = 0;

	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] == 0)
		{
			board[i] = playerNum;

			int temp = maxSearch(board, depth + 1, playerNum);

			if (temp < score)
			{
				score = temp;
				chosenMove = i;
			}
			board[i] = 0;
		}
	}

	return chosenMove;
}

int maxSearch(vector<int> & board, int depth, int & playerNum)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{ 
		if (depth == 3)
			return 0;
		int score = std::numeric_limits<int>::min();

		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == 0)
			{
				if (playerNum == 1)
					board[i] = 2;
				else
					board[i] = 1;
				score = std::max(score, minSearch(board, depth + 1, playerNum));
				board[i] = 0;
			}
		}

		return score;
	}
	else // other player wins
		return 10;
}

int minSearch(vector<int>& board, int depth, int& playerNum)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum)
		return -10;
	else if (winStatus == 3)
		return 0;
	else if (winStatus == 0)
	{
		if (depth == 3)
			return 0;
		int score = std::numeric_limits<int>::max();

		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == 0)
			{
				board[i] = playerNum;
				score = std::min(score, maxSearch(board, depth + 1, playerNum));
				board[i] = 0;
			}
		}

		return score;
	}
	else
		return 10;
}

void botTurn(int & playerNum, vector<int>& board)
{
	cout << "It's Player " << playerNum << "'s turn!" << endl;

	//Stuff for making a random move... Once we have a minimax function, only use
	//RNG to choose between multiple best possible moves

	//std::random_device random_device;
	//std::mt19937 engine{ random_device() };
	//std::uniform_int_distribution<int> dist(0, movesList.size() - 1);
	//int chosenMove = movesList[dist(engine)];

	int chosenMove = minimax(board, 0, true, playerNum);
	
	board[chosenMove] = playerNum;
}
