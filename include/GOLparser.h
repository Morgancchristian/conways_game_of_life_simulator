/*
 * Author: Caleb Christian
 * Date: Sep 14, 2025
 */

#ifndef GOLPARSER_H
#define GOLPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class GOLparser {
public:

    GOLparser();

    int tryOpenFile(string& fileName);
    void incrementLineNumber(int& line_number);
    int checkHeader(string& fileName, int& line_number, int& dimension, int& height_from_file);
    int readContentsToVector(string& fileName, int& line_number, vector<string>& lines, int dimension, int height_from_file);
    int vecToBinaryStrAndVec(vector<string>& lines, vector<string>& matrixLikeBinaryVersion, string& binary_string);
};
#endif
