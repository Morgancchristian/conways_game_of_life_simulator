/*
 * Author: Caleb Christian
 * Date: October 1, 2025
 */

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <string>
#include <vector>

using namespace std;

class GameOfLife {

private:
    int width;
    int height;
    int generation;
    vector<vector<int>> board;
    string gameString;
    vector<pair<int, int>> liveCellVec;
    bool threeState;
    bool wraparound;

public:

    GameOfLife(int width, int height, string gameString, bool threeState = false, bool wraparound = false);

    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setGeneration(int generation);
    int getGeneration();
    void setGameString(string gameString);
    string getGameString();
    void setBoard(const vector<vector<int>>& newBoard);
    vector<vector<int>> getBoard();
    void setLiveCellVec(const vector<pair<int, int>>&);
    vector<pair<int, int>> getLiveCellVec();

    void initBoard();
    void findLiveCellPos(int row, int col, vector<vector<int>>& currentBoard);
    void clearLiveCellVec();
    void next();
    void nextNGen(int n);
    void printGame();
};
#endif
