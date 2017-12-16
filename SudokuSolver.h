/*
SudokuSolver.h
Zi Jian Wu
CSCI 235
Assignment 3
11/8/2016
*/
#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>
#include "StackInterface.h"
#include "Node.h"
#include "LinkedStack.h"

using namespace std;

class SudokuSolver
{
public:
	//Constructor, reads the file and assgins each number into a 2D array in its respective slot.
	SudokuSolver(string filename);

	//@param maxBackSteps is approixmately how many tiems pop() will be called also known as how many times we will backtrack for a the puzzle
	//If puzzle is solved it will return true
	//If puzzle is not solved within maxBackSteps count it will return false
	bool SolvePuzzle(int maxBackSteps);

	//Displays the current state of the puzzle
	void DisplayPuzzle();

private:
	//@param number is the digit that will be inserted into the puzzle at position 
	//@param [row][col] is the slot that the number will be inserted into
	//Returns true if number is a valid input
	//Returns false if number is invalid input
	bool insert(int number, int row, int col);

	//@param [row][col] will be set to 0
	//Returns true if row and col are valid positions
	//Returns false if row or col are invalid positions 
	bool remove(int row, int col);

	//Goes back to the index of the zero before in our indexOfZeroes[] Array and sets it to our currentIndex
	//Used for the stack to keep note of the indexes when backtracking
	//returns true if we had something to go back to
	//returns false if currentIndex is less than 0 meaning no solution to puzzle
	bool goBack();

	//Returns the index in the range 1-81 if not solved 
	//If nextEmpty() returns 0, then the puzzle is solved
	int nextEmpty();

	//@param row = positon x, col = positon y for sudokuPuzzle[x][y]
	//Returns the missing number(s) in lowest to highest order in one integer in the 3x3 box of specified row and col
	int getMissingInBox(int row, int col);

	//@param row = positon x in sudokuPuzzle[x][y]
	//Returns the missing number(s) in lowest to highest order in one integer of the row
	int getMissingInRow(int row);

	//@param col = positon y in sudokuPuzzle[x][y]
	//Returns the missing number(s) in lowest to highest order in one integer of the column
	int getMissingInCol(int col);

	//@param string filename is the name of the puzzle file to solve 
	//Inserts the puzzle in the file into the 2D array sudokuPuzle[9][9]
	//Returns true if file read correctly
	//Returns false if file failed to read 
	bool readInputFile(string filename);

	//Stack to keep track of numbers to try
	LinkedStack<int> stack;

	//2D array to store the puzzle
	int sudokuPuzzle[9][9];

	//Keep track of the index that we are trying different numbers on
	int currentIndex;

	//Keeps track of our last zero index so we can backtrack easier and also not try to change the numbers that are given in the puzzle
	int currentIndexOfArray;

	//Index of all the zeroes in the puzzle
	int indexOfZeroes[81];
};

#include "Node.cpp"
#include "LinkedStack.cpp"
#endif