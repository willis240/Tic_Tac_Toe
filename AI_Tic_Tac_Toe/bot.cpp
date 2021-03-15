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
			chosenMove = monteCarlo(board, playerNum, timeForAI, movesMade);
	}
	else
	{
		if (typeAItwo == 1)
			chosenMove = minimax(board, 0, playerNum, timeForAI);
		else
			chosenMove = monteCarlo(board, playerNum, timeForAI, movesMade);
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
Node root;
int monteCarlo(vector<char>& board, int& playerNum, const int & timeForAI, const vector<int> & movesMade)
{
	int boardsChecked = 0;
	bool turn = true;
	if (playerNum == 2)
		turn = false;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	bool flag = true;
	for (const auto& a : root.children)
	{
		if (a.board == board)
		{
			root = a;
			simulations = a.sims;
			flag = false;
			break;
		}
	}

	if (flag)
	{
		root = Node(board, 0, 0, 0, turn);
		simulations = 0;
	}

	//Primary loop of the MCTS;
	//Finds node with best UCT then performs rollout and backpropagation
	while (duration.count() < timeForAI)
	{
		start = std::chrono::high_resolution_clock::now();
		
		findBestUCT(root, boardsChecked);

		end = std::chrono::high_resolution_clock::now();
		duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	}

	float highestUCT = 0.0;
	for (const auto& a : root.children)
	{
		if (a.uct > highestUCT)
			highestUCT = a.uct;
	}

	for (const auto& a : root.children)
	{
		if (highestUCT == a.uct)
		{
			root = a;
			simulations = a.sims;

			//checks for the move made by the node with the best UCT, then returns it
			for (int i = 0; i < board.size(); i++)
			{
				if (board[i] != root.board[i])
				{
					cout << "Boards checked: " << boardsChecked << endl;
					cout << "Boards/sec: " << boardsChecked / (timeForAI / 1000000) << endl;
					cout << "Move made: " << i << endl;
					return i;
				}
			}
		}
	}

}

const float constant = 1.5;
//uses UCT equation to find & return node with the highest UCT
bool findBestUCT(Node & node, int & boardsChecked)
{
	bool result = false;

	float bestUCT = node.uct;

	for (const auto& a : node.children)
	{
		if (a.uct > bestUCT)
			bestUCT = a.uct;
	}

	if (bestUCT == node.uct)
		result = rollout(node, boardsChecked);
	else
	{
		for (auto& a : node.children)
		{
			if (bestUCT == a.uct)
			{
				result = findBestUCT(a, boardsChecked);
				break;
			}
		}
	}

	if (result == node.turn)
		node.wins++;
	node.sims++;

	node.uct = ((double)node.wins / (double)node.sims) + constant * sqrt(log(double(simulations)) / double(node.sims));
	return result;
}

//traverses down a path of the tree using random choices for both self and opponent
bool rollout(Node & node, int & boardsChecked)
{
	simulations++;

	int simTurn;
	if (node.turn)
		simTurn = 2;
	else
		simTurn = 1;

	bool flag = true;

	vector<char> newBoard = node.board;
	vector<char> availableMoves;
	for (int i = 0; i < newBoard.size(); i++)
	{
		if (newBoard[i] == 0)
			availableMoves.push_back(i);
	}

	//Remove children's moves from availableMoves
	for (const auto& a : node.children)
	{
		for (int i = 0; i < a.board.size(); i++)
		{
			if (newBoard[i] != a.board[i])
			{
				availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), i), availableMoves.end());
			}
		}
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	if (winCheck(newBoard) == 0)
	{
		int firstRand;
		if (availableMoves.size() > 1)
		{
			std::uniform_int_distribution<int> randval(0, availableMoves.size() - 1);
			firstRand = randval(gen);
		}
		else
		{
			firstRand = 0;
		}
		int firstRandMove = availableMoves[firstRand];
		newBoard[firstRandMove] = simTurn;
		availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), firstRandMove), availableMoves.end());
	}
	Node tempNode(newBoard, 0, 1, 0, !(node.turn));
	vector<char> boardWorking = newBoard;
	bool turnWorking = !(node.turn);
	int counter = 0;

	if (winCheck(boardWorking) == 0)
	{
		int moveTest;
		if (turnWorking)
			moveTest = 2;
		else
			moveTest = 1;

		int secondRand;
		int secondRandMove = 0;
		if (availableMoves.size() > 1)
		{
			std::uniform_int_distribution<int> randval(0, availableMoves.size() - 1);
			secondRand = randval(gen);
			secondRandMove = availableMoves[secondRand];
			availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), secondRandMove), availableMoves.end());
		}
		else if (availableMoves.size() == 1)
		{
			secondRand = 0;
			secondRandMove = availableMoves[secondRand];
			availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), secondRandMove), availableMoves.end());
		}
		else
		{
			for (int i = 0; i < boardWorking.size(); i++)
			{
				if (boardWorking[i] == 0)
					secondRandMove = i;
			}
		}

		boardWorking[secondRandMove] = moveTest;
		turnWorking = !turnWorking;
		
		boardsChecked++;
	}

	if (node.turn != turnWorking)
		tempNode.wins++;

	tempNode.uct = ((double)tempNode.wins / (double)tempNode.sims) + constant * sqrt(log((double)simulations) / (double)tempNode.sims);
	node.children.push_back(tempNode);

	return turnWorking;
}