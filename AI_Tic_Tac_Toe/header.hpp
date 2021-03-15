// header.hpp
// William Fisher
// Jan. 26, 2021

#ifndef HEADER_HPP
#define HEADER_HPP

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <math.h>

struct Node {
    std::vector<char> board;
    int wins;
    int sims;
    float uct;
    bool turn;
    std::vector<Node> children;

    Node() : board(25, 0), wins(0), sims(0), uct(0), turn(false) {};
    Node(std::vector<char> boardInput, int winsInput, int simsInput, float uctInput, bool turnInput) :
        board(boardInput), wins(winsInput), sims(simsInput), uct(uctInput), turn(turnInput) {};
};

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
    std::vector<int>& movesMade, std::vector<int> & moves, const char & typeAIone, const char & typeAItwo,
    const int& timeForAI);
void askForSave(const std::vector<int>& movesMade);

// bot.cpp
char selectAI();
int selectTime();
void botTurn(int& playerNum, std::vector<char>& board, std::vector<int>& movesMade,
    const char & typeAIone, const char & typeAItwo, const int& timeForAI);
int minimax(std::vector<char> & board, int depth, int & playerNum, const int& timeForAI);
int maxSearch(std::vector<char> & board, int depth, int& playerNum, int & boardsChecked, const int& timeForAI,
    std::chrono::steady_clock::time_point& start);
int minSearch(std::vector<char>& board, int depth, int& playerNum, int & boardsChecked, const int& timeForAI,
    std::chrono::steady_clock::time_point& start);
int evalFunc(int& playerNum, std::vector<char> board);
int monteCarlo(std::vector<char>& board, int& playerNum, const int& timeForAI, const std::vector<int> & movesMade);
bool findBestUCT(Node& root, int& boardsChecked);
bool rollout(Node& node, int& boardsChecked);

#endif
