// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "Grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

void printWelcome();
void inputData(Grid<bool>& Matrix);
void printData(const Grid<bool>& Matrix);
int askFrames();
void animate(Grid<bool>& Matrix, int num_frames);
void tick(Grid<bool>& Matrix);
void simulateOneStep(Grid<bool>& Matrix);

int main() {
    // TODO: Finish the program!
    printWelcome();

    Grid<bool> lifeMat;
    inputData(lifeMat);
    printData(lifeMat);

    string flag;
    string promptStr = "a)nimate, t)ick, q)uit ?";
    while (true) {
        flag = toLowerCase(getLine(promptStr));
        if (flag == "a") {
            int num_frames = askFrames();
            animate(lifeMat, num_frames);
        } else if (flag == "t") {
            tick(lifeMat);
        } else if (flag == "q") {
            break;
        } else {
            cout << "Illegal input, please input 'a', 't' or 'q'. " << endl;
        }
    }

    cout << "Have a nice Life!" << endl;
    return 0;
}

void printWelcome() {
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
}


// This function returns a ifstream by reading from data files provided by users.
// The user provide a file name. The computer will prompt until an effective file is opened.
// This function then reads input data line by line and genereate a Grid<bool><bool> based on the data.
void inputData(Grid<bool>& Matrix) {

    ifstream inputData;
    string fileName = getLine("Grid<bool><bool> input file name? ");
    inputData.open(fileName.c_str());
    while (inputData.fail()) {
        cout << "Unable to open that file. Try again. " << endl;
        fileName = getLine("Grid<bool><bool> input file name? ");
        inputData.open(fileName.c_str());
    }

    string line;
    getline(inputData, line);
    int num_Row = stringToInteger(line);
    cout << "Number of rows is " << num_Row << endl;
    getline(inputData, line);
    int num_Col = stringToInteger(line);
    cout << "Number of columns is " << num_Col << endl;
    Matrix.resize(num_Row, num_Col);

    for (int i = 0; i < num_Row; i++) {
        getline(inputData, line);
        for (int j = 0; j < num_Col; j++) {
            if (line[j] == '-') {
                Matrix[i][j] = false;
            } else if (line[j] == 'X') {
                Matrix[i][j] = true;
            } else {
                cout << "Incorrect input! please only use legal input '-' or 'X'! " << endl;
                break;
            }
        }
    }

    inputData.close();
}


void printData(const Grid<bool>& Matrix){
    for (int i = 0; i < Matrix.height(); i++) {
        for (int j = 0; j < Matrix.width(); j++) {
            if (Matrix[i][j] == false) {
                cout << "-";
            } else {
                cout << "X";
            }
        }
        cout << endl;
    }
}

int askFrames(){

    string num_frames_str = getLine("How many frames? ");
    while (!stringIsInteger(num_frames_str)) {
        cout << "Illegal integer format. Try again" << endl;
        num_frames_str = getLine("How many frames? ");
    }
    int num_frames = stringToInteger(num_frames_str);
    return num_frames;
}

void animate(Grid<bool>& Matrix, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        clearConsole();
        simulateOneStep(Matrix);
        pause(50);
    }
}

void tick(Grid<bool>& Matrix) {
    simulateOneStep(Matrix);
}

void simulateOneStep(Grid<bool>& Matrix) {
    Grid<bool> new_Mat(Matrix.height(), Matrix.width()); // the result grid that goes one step
    int num_neighbor;
    for (int i = 0; i < Matrix.height(); i++) {
        for (int j = 0; j < Matrix.width(); j++) {
            num_neighbor = 0;
            for (int m = -1; m < 2; m++) {
                for (int n = -1; n < 2; n++) {
                    if (Matrix.inBounds(i+m, j+n)) {
                        if (Matrix[i+m][j+n] == true && (m != 0 || n != 0)) {
                            num_neighbor++;
                        }
                    }
                }
            }
            if (num_neighbor == 0) {
                new_Mat[i][j] = false;
            } else if (num_neighbor == 1) {
                new_Mat[i][j] = false;
            } else if (num_neighbor == 2) {
                new_Mat[i][j] = Matrix[i][j];
            } else if (num_neighbor == 3) {
                new_Mat[i][j] = true;
            } else if (num_neighbor >= 4) {
                new_Mat[i][j] = false;
            } else {
                cout << "The number of neighbors should not be negative! " << endl;
                break;
            }
        }
    }
    Matrix = new_Mat;
    printData(Matrix);
}


