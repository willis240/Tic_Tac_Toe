// bot.cpp
// William Fisher
// Feb. 4, 2021

#include "header.hpp"
using std::cout;
using std::endl;
using std::vector;
using std::queue;

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
			chosenMove = minimax(board, 0, playerNum, timeForAI);
		else
			chosenMove = monteCarlo(board, playerNum, timeForAI);
	}
	else
	{
		if (typeAItwo == 1)
			chosenMove = minimax(board, 0, playerNum, timeForAI);
		else
			chosenMove = monteCarlo(board, playerNum, timeForAI);
	}

	board[chosenMove] = playerNum;
	movesMade.push_back(chosenMove);
}

int minimax(vector<char> & board, int depth, int & playerNum, const int & timeForAI)
{
	auto start = std::chrono::high_resolution_clock::now();
	int boardsChecked = 0;
	int score = std::numeric_limits<int>::max();
	int chosenMove = 0;

	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] == 0)
		{
			board[i] = playerNum;

			int temp = maxSearch(board, depth + 1, playerNum, boardsChecked, timeForAI, start);

			if (temp < score)
			{
				score = temp;
				chosenMove = i;
			}
			board[i] = 0;
		}
	}
	cout << "Boards processed: " << boardsChecked << endl;
	cout << "Boards/sec: " << boardsChecked / (timeForAI / 1000000) << endl;
	return chosenMove;
}

int maxSearch(vector<char> & board, int depth, int & playerNum, int & boardsChecked,
	const int & timeForAI, std::chrono::steady_clock::time_point & start)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{ 
		int score = std::numeric_limits<int>::min();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		if (depth == maxDepth || duration.count() > timeForAI)
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
				score = std::max(score, minSearch(board, depth + 1, playerNum, boardsChecked, timeForAI, start));
				boardsChecked++;
				board[i] = 0;
			}
		}

		return score;
	}
	else // other player wins
		return 10;
}

int minSearch(vector<char>& board, int depth, int& playerNum, int & boardsChecked,
	const int& timeForAI, std::chrono::steady_clock::time_point& start)
{
	int winStatus = winCheck(board);
	if (winStatus == playerNum) // current bot wins
		return -10;
	else if (winStatus == 3) // tie
		return 0;
	else if (winStatus == 0) // game still ongoing
	{
		int score = std::numeric_limits<int>::max();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		if (depth == maxDepth || duration.count() > timeForAI)
		{
			score = std::min(score, evalFunc(playerNum, board));
			return score;
		}

		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == 0)
			{
				board[i] = playerNum;
				score = std::min(score, maxSearch(board, depth + 1, playerNum, boardsChecked, timeForAI, start));
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

int simulations = 0;
int monteCarlo(vector<char>& board, int& playerNum, const int & timeForAI)
{
	cout << "I am the Monte Carlo function! I'm currently a dummy!" << endl;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	simulations = 0;

	//initial random move
	vector<char> availableMoves;
	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] == 0)
			availableMoves.push_back(i);
	}

	//THIS IS IN PLACE OF INITIAL ROLLOUT, REPLACE WITH ROLLOUT!!!!!!!!!!!!!
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, availableMoves.size());
	int randomMove = int(availableMoves[dist(mt)]);
	simulations++;

	//while (duration.count() < timeForAI)
	//{
		start = std::chrono::high_resolution_clock::now();

		Node * root = new Node();
		//theoretical code that will likely become real code once data structure is locked down
		Node * node = bestUCT(root);
		//rollout(node, availableMoves);
		//updateStats(node);
		simulations++;

		end = std::chrono::high_resolution_clock::now();
		duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	//}
	return randomMove;
}

//uses UCT equation to find & return node with the highest UCT
Node * bestUCT(Node * root)
{
	double bestUCT = 0.0;
	double tempUCT = 0.0;
	Node* bestNode = root;
	const int constant = 1.5;

	queue<Node*> q;
	q.push(root);

	//Makes a tree for testing. REMOVE LATER!!!!!!!!!!!!!!!!!!!!!!!!!
	(root->children).push_back(new Node(2));
	(root->children).push_back(new Node(3));
	(root->children[0]->children).push_back(new Node(4));
	(root->children[0]->children[0]->children).push_back(new Node(7));
	(root->children[0]->children[0]->children[0]->children).push_back(new Node(9));
	(root->children[1]->children).push_back(new Node(10));
	(root->children[1]->children[0]->children).push_back(new Node(12));

	//iterates through a queue containing all the nodes
	while (!q.empty())
	{
		int n = q.size();
		while (n > 0)
		{
			Node* p = q.front();
			q.pop();

			tempUCT = (double(p->wins) / double(p->trials)) + constant * std::sqrt(log(double(simulations)) / double(p->trials));

			if (bestUCT < tempUCT)
			{
				bestUCT = tempUCT;
				bestNode = p;
			}

			for (int i = 0; i < p->children.size(); i++)
				q.push(p->children[i]);
			n--;
		}
	}
	return (bestNode);
}

//traverses down a path of the tree using random choices for both self and opponent
void rollout(Node & node, vector<char>& availableMoves)
{

}

//traverses back up through the path of the tree, updating wins / trials for each node along the path
//note that each odd-depth node is an opponent's node, and should have losses where self's have wins
void updateStats(Node & node)
{

}