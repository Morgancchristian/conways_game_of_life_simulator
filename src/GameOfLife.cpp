/*
 * Author: Caleb Christian
 * Date: October 1, 2025
 */

#include "GameOfLife.h"
#include <iostream>

using namespace std;

GameOfLife::GameOfLife(int width, int height, string gameString, bool threeState, bool wraparound) : width(width), height(height), generation(0), gameString(gameString), threeState(threeState), wraparound(wraparound){}

void GameOfLife::setWidth(int width) {
    this->width = width;
}

int GameOfLife::getWidth() {
    return this->width;
}

void GameOfLife::setHeight(int height) {
    this->height = height;
}

int GameOfLife::getHeight() {
    return this->height;
}

void GameOfLife::setGeneration(int generation) {
    this->generation = generation;
}

int GameOfLife::getGeneration() {
    return this->generation;
}

void GameOfLife::setGameString(string gameString) {
    this->gameString = gameString;
}

string GameOfLife::getGameString() {
    return this->gameString;
}

void GameOfLife::setBoard(const vector<vector<int>>& board) {
    this->board = board;
}

vector<vector<int>> GameOfLife::getBoard() {
    return this->board;
}

void GameOfLife::setLiveCellVec(const vector<pair<int, int>>& liveCellVec) {
    this->liveCellVec = liveCellVec;
}

vector<pair<int, int>> GameOfLife::getLiveCellVec() {
    return this->liveCellVec;
}

void GameOfLife::initBoard() {
    int numOfRows = getHeight();
    int numOfCol = getWidth();
    string gameString = getGameString();
    vector<vector<int>> initialBoard(numOfRows, vector<int>(numOfCol, 0));

    for(int row = 0; row < numOfRows; row++) {
        for(int col = 0; col < numOfCol; col++) {
            int gameStrIdx = row * numOfCol + col;
            if(gameString[gameStrIdx] == '1') {
                initialBoard[row][col] = 1;
            }
        }
    }
    setBoard(initialBoard);
}

int getWrappedIndex(int col, int numCol) {
    if (col < 0) {
        return numCol + col;
    } else if (col >= numCol) {
        return col % numCol;
    }
    return col;
}

void GameOfLife::findLiveCellPos(int row, int col, vector<vector<int>>& currentBoard) {
    liveCellVec = getLiveCellVec();

    int numRows = currentBoard.size();
    int numCols = currentBoard[0].size();

    // Left
    int leftCol = col - 1;
    if (wraparound) {
        leftCol = getWrappedIndex(leftCol, numCols);
    }
    if ((wraparound || col > 0) && (int)currentBoard[row][leftCol] == 1) {
        liveCellVec.push_back({row, leftCol});
    }

    // Right
    int rightCol = col + 1;
    if (wraparound) {
        rightCol = getWrappedIndex(rightCol, numCols);
    }
    if ((wraparound || col < numCols - 1) && (int)currentBoard[row][rightCol] == 1) {
        liveCellVec.push_back({row, rightCol});
    }

    // Up
    int upRow = row - 1;
    if (wraparound) {
        upRow = getWrappedIndex(upRow, numRows);
    }
    if ((wraparound || row > 0) && (int)currentBoard[upRow][col] == 1) {
        liveCellVec.push_back({upRow, col});
    }

    // Down
    int downRow = row + 1;
    if (wraparound) {
        downRow = getWrappedIndex(downRow, numRows);
    }
    if ((wraparound || row < numRows - 1) && (int)currentBoard[downRow][col] == 1) {
        liveCellVec.push_back({downRow, col});
    }

    // Up-Left diagonal
    int diagUpRow = row - 1;
    int diagLeftCol = col - 1;
    if (wraparound) {
        diagUpRow = getWrappedIndex(diagUpRow, numRows);
        diagLeftCol = getWrappedIndex(diagLeftCol, numCols);
    }
    if ((wraparound || (row > 0 && col > 0)) && (int)currentBoard[diagUpRow][diagLeftCol] == 1) {
        liveCellVec.push_back({diagUpRow, diagLeftCol});
    }

    // Up-Right diagonal
    int diagUpRow2 = row - 1;
    int diagRightCol = col + 1;
    if (wraparound) {
        diagUpRow2 = getWrappedIndex(diagUpRow2, numRows);
        diagRightCol = getWrappedIndex(diagRightCol, numCols);
    }
    if ((wraparound || (row > 0 && col < numCols - 1)) && (int)currentBoard[diagUpRow2][diagRightCol] == 1) {
        liveCellVec.push_back({diagUpRow2, diagRightCol});
    }

    // Down-Left diagonal
    int diagDownRow = row + 1;
    int diagLeftCol2 = col - 1;
    if (wraparound) {
        diagDownRow = getWrappedIndex(diagDownRow, numRows);
        diagLeftCol2 = getWrappedIndex(diagLeftCol2, numCols);
    }
    if ((wraparound || (row < numRows - 1 && col > 0)) && (int)currentBoard[diagDownRow][diagLeftCol2] == 1) {
        liveCellVec.push_back({diagDownRow, diagLeftCol2});
    }

    // Down-Right diagonal
    int diagDownRow2 = row + 1;
    int diagRightCol2 = col + 1;
    if (wraparound) {
        diagDownRow2 = getWrappedIndex(diagDownRow2, numRows);
        diagRightCol2 = getWrappedIndex(diagRightCol2, numCols);
    }
    if ((wraparound || (row < numRows - 1 && col < numCols - 1)) && (int)currentBoard[diagDownRow2][diagRightCol2] == 1) {
        liveCellVec.push_back({diagDownRow2, diagRightCol2});
    }

    setLiveCellVec(liveCellVec);
}

void GameOfLife::clearLiveCellVec() {
    liveCellVec.clear();
}

void GameOfLife::next() {
    generation = getGeneration() + 1;
    board = getBoard();
    vector<vector<int>> currentBoard = board;
    int numOfRows = getHeight();
    int numOfCol = getWidth();

    for(int row = 0; row < numOfRows; row++) {
        for(int col = 0; col < numOfCol; col++) {
            clearLiveCellVec();
            findLiveCellPos(row, col, currentBoard);
            liveCellVec = getLiveCellVec();
            int aliveNeighbors = liveCellVec.size();

            if (threeState) {
                if (currentBoard[row][col] == 1){
                    if (aliveNeighbors == 2 || aliveNeighbors == 3) {
                        board[row][col] = 1;
                    } else {
                        board[row][col] = 2;
                    }
                } else if (currentBoard[row][col] == 2) {
                    board[row][col] = 0;
                } else {
                    if (aliveNeighbors == 3) {
                        board[row][col] = 2;
                    }
                }
            } else {
                if (board[row][col] == 1 && (aliveNeighbors < 2)) {
                    board[row][col] = 0;
                } else if (board[row][col] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
                    board[row][col] = 1;
                } else if (board[row][col] == 1 && (aliveNeighbors > 3)) {
                    board[row][col] = 0;
                } else if (board[row][col] == 0 && aliveNeighbors == 3) {
                    board[row][col] = 1;
                }
            }
        }
    }
    setGeneration(generation);
    setBoard(board);
}

void GameOfLife::nextNGen(int n) {
    if (n <= 0) return;
    for (int i = 0; i < n; i++) {
        next();
    }
}

void GameOfLife::printGame() {
    generation = getGeneration();
    board = getBoard();
    int numOfRows = getHeight();
    int numOfCol = getWidth();

    cout << "Generation: " << generation << endl;

    for(int row = 0; row < numOfRows; row++) {
        for(int col = 0; col < numOfCol; col++) {
            if (threeState && board[row][col] == 2) {
                cout << 'D';
            } else {
                cout << board[row][col];
            }
        }
        cout << endl;
    }
}
