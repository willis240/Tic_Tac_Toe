// header.hpp
// William Fisher
// Jan. 26, 2021

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <algorithm>

int selectMode();
void placeMarker(int slot, std::vector<int>& board);
void drawBoard(std::vector<int>& board);
void playerTurn(int playerNum, std::vector<int>& board);
void playbackTurn(int playerNum, std::vector<int>& board);
int getResult(const std::vector<int>& check);
bool tieCheck(std::vector<int>& board);
int winCheck(std::vector<int>& board);
void turnOrder(int& playerNum, std::vector<int>& board, const int & choice, const int& turnCount);

int evalFunc(int & playerNum, std::vector<int> board);
int minimax(std::vector<int> & board, int depth, bool isMaximizingPlayer, int & playerNum);
int maxSearch(std::vector<int> & board, int depth, int& playerNum);
int minSearch(std::vector<int>& board, int depth, int& playerNum);
void botTurn(int & playerNum, std::vector<int>& board);

#endif
