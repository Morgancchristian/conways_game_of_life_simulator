/*
 * Author: Caleb Christian
 * Date: Sep 14, 2025
 */

#include "GOLparser.h"

using namespace std;


GOLparser::GOLparser() {}


int GOLparser::tryOpenFile(string& fileName) {
    ifstream file_input;
    file_input.open(fileName);
    if(!file_input) {
        cerr << "Error: Can not open file: " << fileName << endl;
        return 1;
    }
    return 0;
}


void GOLparser::incrementLineNumber(int& line_number) {
    line_number++;
}


int GOLparser::checkHeader(string& fileName, int& line_number, int& dimension, int& height_from_file) {
    ifstream file_input;
    file_input.open(fileName);

    string header;
    getline(file_input, header);

    if (header.empty()) {
        cerr << "Error: There is no header. " << line_number << endl;
        cerr << "Return Code: " << line_number + 1 << endl;
        return 1;
    }

    string num1, num2;
    bool space_found = false;

    for (char i : header) {
        if (i != ' ' && (i < '0' || i > '9')) {
            cerr << "Error: Invalid header on line " << line_number << endl;
            cerr << "Return Code: " << line_number + 1 << endl;
            return 1;
        }
        if (i == ' ') {
            space_found = true;
            continue;
        }
        if (!space_found) {
            num1 += i;
        } else {
            num2 += i;
        }
    }

    if (num1.empty() || num2.empty()) {
        cerr << "Error: Header must contain two numbers separated by a space on line " << line_number << std::endl;
        cerr << "Return Code: " << line_number + 1 << endl;
        return 1;
    }

    for (char c : num1) {
        if (c < '0' || c > '9') {
            cerr << "Error: Invalid width on line " << line_number << endl;
            return 1;
        }
    }
    for (char c : num2) {
        if (c < '0' || c > '9') {
            cerr << "Error: Invalid height on line " << line_number << endl;
            return 1;
        }
    }

    dimension = stoi(num2);
    height_from_file = stoi(num1);

    if (dimension < 0 || height_from_file < 0) {
        cerr << "Error: Invalid dimensions on line " << line_number << endl;
        cerr << "Return Code: " << line_number + 1 << endl;
        return 1;
    }
    return 0;
}


int GOLparser::readContentsToVector(string& fileName, int& line_number, vector<string>& lines, int dimension, int height_from_file) {
    ifstream file_input;
    file_input.open(fileName);

    string line;

    getline(file_input, line);

    while(getline(file_input, line)) {
        incrementLineNumber(line_number);

        if (line.empty()) {
            continue;
        }

        string clean_line;

        for(char c : line) {
            if (c != 'O' && c != 'X' && c != ' ' && c != '\t') {
                cerr << "Error: Invalid character on line " << line_number << endl;
                cerr << "Return Code: " << line_number + 1 << endl;
                return 1;
            }
            if(c != ' ' && c != '\t') {
                clean_line += c;
            }
        }
        if (static_cast<int>(clean_line.length()) != dimension) {
            cerr << "Error: Invalid line length on line " << line_number << endl;
            cerr << "Return Code: " << line_number + 1 << endl;
            return 1;
        }
        lines.push_back(clean_line);
    }
    if (static_cast<int>(lines.size()) != height_from_file) {
        cerr << "Error: Conflict with header, line does not exist on line:  " << line_number + 1 << endl;
        cerr << "Return Code: " << line_number + 1 << endl;
        return 1;
    }
    return 0;
}


int GOLparser::vecToBinaryStrAndVec(vector<string>& lines, vector<string>& matrixLikeBinaryVersion, string& binary_string) {
    for (int q = 0; q < static_cast<int>(lines.size()); q++) {
        string row_binary;
        for (char c : lines[q]) {
            if (c == 'O') {
                binary_string += "1";
                row_binary += "1";
            } else {
                binary_string += "0";
                row_binary += "0";
            }
        }
        matrixLikeBinaryVersion.push_back(row_binary);
    }
    return 0;
}
