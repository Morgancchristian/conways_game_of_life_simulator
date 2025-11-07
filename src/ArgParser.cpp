/*
 * Author: Caleb Christian
 * Date: Oct 30, 2025
 */

#include "ArgParser.h"
#include <getopt.h>
#include <cstring>
using namespace std;

ArgParser::ArgParser(): fileName(""), generations(10), printInterval(1), threeState(false), wraparound(false), outputFile(""), writeToFile(false) {}

int ArgParser::parseArgs(int argc, char* argv[]) {
    int c;

    while ((c = getopt(argc, argv, "f:g:p:o:sw")) != -1) {
        switch (c) {
        case 'f':
            fileName = optarg;
            break;
        case 'g':
            generations = stoi(optarg);
            break;
        case 'p':
            printInterval = stoi(optarg);
            break;
        case 'o':
            outputFile = optarg;
            writeToFile = true;
            break;
        case 's':
            threeState = true;
            break;
        case 'w':
            wraparound = true;
            break;
        case '?':
            return 1;
        default:
            return 1;
        }
    }
    return checkFlags();
}

int ArgParser::checkFlags() {
    if (fileName.empty()) {
        cerr << "Error: No filename was given with -f" << endl;
        return 1;
    }

    if (threeState && wraparound) {
        cerr << "Error: -s and -w cannont be inputs in the same argument" << endl;
        return 1;
    }

    return 0;
}

string ArgParser::getFileName() {
    return this->fileName;
}

int ArgParser::getGenerations() {
    return this->generations;
}

int ArgParser::getPrintInterval() {
    return this->printInterval;
}

bool ArgParser::isThreeState() {
    return this->threeState;
}

bool ArgParser::isWraparound() {
    return this->wraparound;
}

string ArgParser::getOutputFile() {
    return this->outputFile;
}

bool ArgParser::shouldWriteToFile() {
    return this->writeToFile;
}
