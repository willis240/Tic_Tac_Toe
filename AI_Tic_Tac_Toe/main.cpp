// main.cpp
// William Fisher
// Jan. 26, 2021

#include "header.hpp"
using std::vector;
using std::cout;
using std::endl;

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

int main()
{
	drawBoard();
}