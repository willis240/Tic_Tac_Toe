// bot.cpp
// William Fisher
// Feb. 4, 2021

#include "header.hpp"
using std::cout;
using std::endl;
using std::vector;

const int maxDepth = 4;

char selectAI()
{
	cout << "1: The bot uses the Minimax Algorithm to decide its move." << endl;
	cout << "2: The bot uses the Monte Carlo Tree Search to decide its move." << endl;

	while (true)
	{
		int input;
		std::cin >> input;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input. Please input the number of the AI option you'd like to select." << endl;
		}
		else if (input > 0 && input < 3)
			return input;
		else
			cout << "That number does not correspond to any of the available AI options. Please try again." << endl;
	}
}

int selectTime()
{
	while (true)
	{
		int input;
		std::cin >> input;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input. Please input an integer for how many seconds you'd like the bot(s)";
			cout << "to have for their turn(s)." << endl;
		}
		else
			return input;
	}
}

void botTurn(int& playerNum, vector<char>& board, vector<int>& movesMade, const char & typeAIone, const char & typeAItwo,
	const int & timeForAI)
{
	cout << "It's Player " << playerNum << "'s turn!" << endl;

	int chosenMove;
	if (playerNum == 1)
	{
		if (typeAIone == 1)
			chosenMove = minimax(board, 0, playerNum);
		else
			chosenMove = monteCarlo(board, playerNum, timeForAI);
	}
	else
	{
		if (typeAItwo == 1)
			chosenMove = minimax(board, 0, playerNum);
		else
			chosenMove = monteCarlo(board, playerNum, timeForAI);
	}

	board[chosenMove] = playerNum;
	movesMade.push_back(chosenMove);
}

int minimax(vector<char> & board, int depth, int & playerNum)
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

int maxSearch(vector<char> & board, int depth, int & playerNum, int & boardsChecked)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{ 
		int score = std::numeric_limits<int>::min();

		if (depth == maxDepth)
		{
			score = std::max(score, evalFunc(playerNum, board));
			return score;
		}

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

int minSearch(vector<char>& board, int depth, int& playerNum, int & boardsChecked)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{
		int score = std::numeric_limits<int>::max();

		if (depth == maxDepth)
		{
			score = std::min(score, evalFunc(playerNum, board));
			return score;
		}

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

int evalFunc(int& playerNum, vector<char> board)
{
	int points = 0;

	// Prioritizes the central column
	for (int i = 2; i < board.size(); i += 5)
	{
		if (board[i] == playerNum)
			points -= 1;
	}

	return points;
}

int monteCarlo(vector<char>& board, int& playerNum, const int & timeForAI)
{
	cout << "I am the Monte Carlo function! I'm currently a dummy!" << endl;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds > (end - start);
	long timeLimit = timeForAI * 1000000;
	while (duration.count() < timeLimit)
	{
		start = std::chrono::high_resolution_clock::now();

		// This cout simply gives the computer something to do while incrementing time
		cout << "filler" << endl;

		end = std::chrono::high_resolution_clock::now();
		duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	}
	return 5;
}