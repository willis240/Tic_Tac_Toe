// bot.cpp
// William Fisher
// Feb. 4, 2021

#include "header.hpp"
using std::cout;
using std::endl;
using std::vector;

void botTurn(int playerNum, vector<int>& board)
{
	cout << "Wow! I'm a dummy in botTurn!" << endl;
	vector<int> movesList;
	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] == 0)
			movesList.push_back(i);
	}

	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<int> dist(0, movesList.size() - 1);

	int chosenMove = movesList[dist(engine)];
	if (playerNum == 1)
		board[chosenMove] = 1;
	else
		board[chosenMove] = 2;

}