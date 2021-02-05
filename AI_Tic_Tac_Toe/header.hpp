// header.hpp
// William Fisher
// Jan. 26, 2021

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

int selectMode();
void placeMarker(int slot, std::vector<int>& board);
void drawBoard(std::vector<int>& board);
void playerTurn(int playerNum, std::vector<int>& board);
void playbackTurn(int playerNum, std::vector<int>& board);
bool getResult(const std::vector<int>& check);
bool tieCheck(std::vector<int>& board);
bool winCheck(std::vector<int>& board);
void turnOrder(int& playerNum, std::vector<int>& board, const int & choice, const int& turnCount);

void botTurn(int playerNum, std::vector<int>& board);

#endif
