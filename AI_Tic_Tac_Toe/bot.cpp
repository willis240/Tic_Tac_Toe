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

int minimax(vector<int> & board, int depth, int & playerNum)
{
	int boardsChecked = 0;
	int score = std::numeric_limits<int>::max();
	int chosenMove = 0;

	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] == 0)
		{
			board[i] = playerNum;

			int temp = maxSearch(board, depth + 1, playerNum, boardsChecked);

			if (temp < score)
			{
				score = temp;
				chosenMove = i;
			}
			board[i] = 0;
		}
	}
	cout << "Boards processed: " << boardsChecked << endl;
	return chosenMove;
}

int maxSearch(vector<int> & board, int depth, int & playerNum, int & boardsChecked)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{ 
		if (depth == 4)
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
				score = std::max(score, minSearch(board, depth + 1, playerNum, boardsChecked));
				boardsChecked++;
				board[i] = 0;
			}
		}

		return score;
	}
	else // other player wins
		return 10;
}

int minSearch(vector<int>& board, int depth, int& playerNum, int & boardsChecked)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{
		if (depth == 4)
			return 0;
		int score = std::numeric_limits<int>::max();

		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == 0)
			{
				board[i] = playerNum;
				score = std::min(score, maxSearch(board, depth + 1, playerNum, boardsChecked));
				boardsChecked++;
				board[i] = 0;
			}
		}

		return score;
	}
	else // other player wins
		return 10;
}

void botTurn(int & playerNum, vector<int>& board)
{
	cout << "It's Player " << playerNum << "'s turn!" << endl;

	int chosenMove = minimax(board, 0, playerNum);
	
	board[chosenMove] = playerNum;
}
