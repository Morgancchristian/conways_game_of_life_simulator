/*
 * Author: Caleb Christian
 * Date: Oct 30, 2025
 */

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class ArgParser {

private:
    string fileName;
    int generations;
    int printInterval;
    bool threeState;
    bool wraparound;
    int checkFlags();

public:

    ArgParser();

    int parseArgs(int argc, char* argv[]);
    string getFileName();
    int getGenerations();
    int getPrintInterval();
    bool isThreeState();
    bool isWraparound();
};
#endif
