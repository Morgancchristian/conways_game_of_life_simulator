/*
 * Author: Caleb Christian
 * Date: Sep 14, 2025
 */

#include <iostream>
#include <string>
#include <vector>
#include "ArgParser.h"
#include "GOLparser.h"
#include "GameOfLife.h"


using namespace std;

int main(int argc, char *argv[]) {

    ArgParser argParser;
    if (argParser.parseArgs(argc, argv) != 0) {
           return 1;
    }

    string fileName = argParser.getFileName();
    int generations = argParser.getGenerations();
    int printInterval = argParser.getPrintInterval();


    GOLparser fileParser;

    if (fileParser.tryOpenFile(fileName) != 0) {
        return 1;
    }

    int line_number = 1;
    int dimension;
    int height_from_file;

    if (fileParser.checkHeader(fileName, line_number, dimension, height_from_file) != 0) {
        return line_number + 1;
    }

    vector<string> lines;
    if (fileParser.readContentsToVector(fileName, line_number, lines, dimension, height_from_file) != 0) {
        return line_number + 1;
    }

    string binary_string;
    vector<string> matrixLikeBinaryVersion;
    fileParser.vecToBinaryStrAndVec(lines, matrixLikeBinaryVersion, binary_string);


    string gameBoardString = binary_string;
    int width = dimension;
    int height = height_from_file;
    bool isThreeState = argParser.isThreeState();
    bool isWraparound = argParser.isWraparound();

    GameOfLife game(width, height, gameBoardString, isThreeState, isWraparound);
    game.initBoard();
    game.printGame();
    cout << endl;

    for (int gen = 1; gen <= generations; gen++) {
        game.next();
        if (gen % printInterval == 0) {
            game.printGame();
            cout << endl;
        }
    }
    return 0;
}
