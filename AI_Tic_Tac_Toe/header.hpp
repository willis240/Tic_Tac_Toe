// header.hpp
// William Fisher
// Jan. 26, 2021

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

// tic_tac_toe.cpp
int selectMode();
void placeMarker(int slot, std::vector<char>& board);
void drawBoard(std::vector<char>& board);
void playerTurn(int playerNum, std::vector<char>& board, std::vector<int>& movesMade);
std::vector<int> getMoveData();
void playbackTurn(int playerNum, std::vector<char>& board, const int & turnCount, std::vector<int> & moves);
int getResult(const std::vector<char>& check);
bool tieCheck(std::vector<char>& board);
int winCheck(std::vector<char>& board);
void turnOrder(int& playerNum, std::vector<char>& board, const int & choice, const int& turnCount,
    std::vector<int>& movesMade, std::vector<int> & moves);
void askForSave(const std::vector<int>& movesMade);

// bot.cpp
int evalFunc(int & playerNum, std::vector<char> board);
int minimax(std::vector<char> & board, int depth, int & playerNum);
int maxSearch(std::vector<char> & board, int depth, int& playerNum, int & boardsChecked);
int minSearch(std::vector<char>& board, int depth, int& playerNum, int & boardsChecked);
void botTurn(int & playerNum, std::vector<char>& board, std::vector<int>& movesMade);

#endif
