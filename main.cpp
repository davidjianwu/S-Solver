/*
main.cpp
Zi Jian Wu
CSCI 235
Assignment 3
11/8/2016

This program solves a sudoku puzzle
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "StackInterface.h"
#include "Node.h"
#include "LinkedStack.h"
#include "SudokuSolver.h"

using namespace std;

int main()
{
	//char solveAgain;
	const int backs = 10000000;
	SudokuSolver Puz("puzzle.txt");
	cout << "**************Original Puzzle*************" << endl << endl;
	Puz.DisplayPuzzle();
	Puz.SolvePuzzle(backs);
	/* *****could not get this part working in time*****
	while(Puz.SolvePuzzle(backs) == 0)
	{
		cout <<"Puzzle was not solved in about" << backs << "backsteps", Continue solve? (y) or (n)" << endl;
		cin >> solveAgain;
		if(solveAgain == 'y')
		{
			Puz.SolvePuzzle(backs);
		}
		else if(solveAgain == 'n')
		{
			cout << "Exited, Puzzle was not solved." << endl;
			return 0;
		}
	*/
	cout << "*************Solution to Puzzle*************" << endl;
	Puz.DisplayPuzzle();

	cout << endl;

	return 0;
}