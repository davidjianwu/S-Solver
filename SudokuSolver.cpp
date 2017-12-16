/*
SudokuSolver.cpp
Zi Jian Wu
CSCI 235
Assignment 3
11/8/2016
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "SudokuSolver.h"

using namespace std;

//Power function for stuff
static int Power(int base, int exp)
{
    int temp=base;
    if (exp==0)
    {
        return 1;
    }
    for (int i=1; i<exp; i++)
    {
        base*=temp;
    }
    return base;
}

SudokuSolver::SudokuSolver(string filename)
{
	readInputFile(filename);
}

bool SudokuSolver::readInputFile(string filename)
{
	ifstream puzzle;
	string inputName = filename;
	puzzle.open(inputName.c_str());

	//Test if file opened, if not, return false and exit program
	if(!puzzle.is_open())
	{
		cout << "File Failed to Open, Exited" << endl;
		return false;
		exit(EXIT_FAILURE);
	}

	while(!puzzle.eof())
	{
		int number;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				puzzle >> number;
				sudokuPuzzle[i][j] = number;
			}
		}
	}
	puzzle.close();
}

int SudokuSolver::getMissingInBox(int row, int col)
{
	//Calcuate where the box starts for the give row and col
	int rowStart;
	int colStart;

	if(row % 3 == 0)
	{
		rowStart = row;
	}
	else if(row % 3 == 1)
	{
		rowStart = row-1;
	}
	else if(row % 3 == 2)
	{
		rowStart = row-2;
	}

	if(col % 3 == 0)
	{
		colStart = col;
	}
	else if(col % 3 == 1)
	{
		colStart = col-1;
	}
	else if(col % 3 == 2)
	{
		colStart = col-2;
	}

	//Array missing[] is to mark off what we have missing so we can store the numbers that are missing into the array finalMissing[] later
	int missing[10];

	for (int i = 0; i < 10; i++)
	{
		missing[i] = 1;
	}

	//mark all values at our missing[] indexies as 0 to to note that they are not missing
	for(int i = rowStart; i<rowStart+3; i++)
	{
		for(int j = colStart; j<colStart+3; j++)
		{
			missing[sudokuPuzzle[i][j]] = 0;
		}
	}

	//Array finalMissing[] is to store the missing numbers
	int finalMissing[9];
	int missingCount = 0;
	for(int i = 0; i < 10; i++)
	{
		if(missing[i] == 1)
		{
			finalMissing[missingCount] = i;
			missingCount++;
		}
	}

	//Create a intger with return value of the missing digits
	int retVal = 0;
	int exponent = missingCount-1;
	for(int i = 0; i < missingCount; i++)
	{
		retVal+= finalMissing[i] * Power(10,exponent);
		exponent--;
	}
	return retVal;
}

int SudokuSolver::getMissingInRow(int row)
{
	int missing[10];

	//initilize all to 1
	for (int i = 0; i < 10; i++)
	{
		missing[i] = 1;
	}

	//mark the ones that are not missing
	for(int i = row; i < row+1; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			missing[sudokuPuzzle[i][j]] = 0;
		}
	}

	//Place missing numbers into another array
	int finalMissing[9];
	int missingCount = 0;
	for(int i = 0; i < 10; i++)
	{
		if(missing[i] == 1)
		{
			finalMissing[missingCount] = i;
			missingCount++;
		}
	}

	//Change into one integer
	int retVal = 0;
	int exponent = missingCount-1;
	for(int i = 0; i < missingCount; i++)
	{
		retVal+= finalMissing[i] * Power(10,exponent);
		exponent--;
	}
	return retVal;	
}

int SudokuSolver::getMissingInCol(int col)
{

	int missing[10];

	//initialize all to 1
	for (int i = 0; i < 10; i++)
	{
		missing[i] = 1;
	}

	//mark the ones that are not missing
	for(int i = col; i < col+1; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			missing[sudokuPuzzle[j][i]] = 0;
		}
	}

	//Place missing numbers into another array
	int finalMissing[9];
	int missingCount = 0;
	for(int i = 0; i < 10; i++)
	{
		if(missing[i] == 1)
		{
			finalMissing[missingCount] = i;
			missingCount++;
		}
	}

	//Change into one integer
	int retVal = 0;
	int exponent = missingCount-1;
	for(int i = 0; i < missingCount; i++)
	{
		retVal+= finalMissing[i] * Power(10,exponent);
		exponent--;
	}
	return retVal;
}
bool SudokuSolver::insert(int number, int row, int col)
{
	//Assign missing numbers to a variable so we can get each digit later
	int missingInBox = getMissingInBox(row,col);
	int missingInRow = getMissingInRow(row);
	int missingInCol = getMissingInCol(col);

	int MIBtemp = missingInBox;
	int MIRtemp = missingInRow;
	int MICtemp = missingInCol;

	int MIB[9]; //Digits missing in the 3x3
	int MIR[9]; //Digits missing in the ROW
	int MIC[9]; //Digits missing in the COLUMN

	//Get size of the integer which are the missing digits so we can use know how many times to use % operator to get each digit
	int lengthOfMIB = 1;
	while(MIBtemp /= 10)
	{
		lengthOfMIB++;
	}

	// Place missing in box digits inside the MIB[] array
	for(int i = lengthOfMIB-1; i >= 0; i--)
	{
		MIB[i] = missingInBox % 10;
		missingInBox /= 10;
	}

	//Get size of the integer which are the missing digits so we can use know how many times to use % operator to get each digit
	int lengthOfMIR = 1;
	while(MIRtemp /= 10)
	{
		lengthOfMIR++;
	}

	// Place missing in ROW digits inside the MIR[] array
	for(int i = lengthOfMIR-1; i >= 0; i--)
	{
		MIR[i] = missingInRow % 10;
		missingInRow /= 10;
	}

	//Get size of the integer which are the missing digits so we can use know how many times to use % operator to get each digit
	int lengthOfMIC = 1;
	while(MICtemp /= 10)
	{
		lengthOfMIC++;
	}

	// Place missing in COLUMN digits inside the MIC[] array
	for(int i = lengthOfMIC-1; i >= 0; i--)
	{
		MIC[i] = missingInCol % 10;
		missingInCol /= 10;
	}

	//Holds the common elements of missing digits in box and missing digits in row
	int intersectTwo[9];
	//size of intersection
	int lengthOfIntTwo = 0;
	int Intersection[9];

	//Fill array of the digits that are common to MIB[] and MIR[]
	for(int i = 0; i < lengthOfMIB; i++)
	{
		for(int j = 0; j < lengthOfMIR; j++)
		{
			if(MIB[i] == MIR[j])
			{
				intersectTwo[lengthOfIntTwo] = MIR[j];
				lengthOfIntTwo++;
				break; // so we dont check extra
			}
		}
	}

	// size of intersection of all 3 arrays
	int lengthOfInt = 0;
	//Fill Intersection[] array with the digits common to MIB[], MIR[] and MIC[]
	for(int i = 0; i < lengthOfIntTwo; i++)
	{
		for(int j = 0; j < lengthOfMIC; j++)
		{
			if(intersectTwo[i] == MIC[j])
			{
				Intersection[lengthOfInt] = MIC[j];
				lengthOfInt++;
				break; // so we dont check extra 
			}
		}
	}

	//Check that the number inserted was a valid number to insert, if it is, return true and add it to puzzle
	for(int i = 0; i < lengthOfInt; i++)
	{
		if(number == Intersection[i])
		{
			sudokuPuzzle[row][col] = number;
			return true;
		}
	}
	//If number was invalid return false and dont add it to puzzle
	return false;
}

bool SudokuSolver::remove(int row, int col)
{
	//Check if valid inputs
	if(row > 8 || row < 0 || col > 8 || col < 0)
	{
		return false;
	}
	sudokuPuzzle[row][col] = 0;
	return true;
}

bool SudokuSolver::goBack()
{
	currentIndexOfArray--;
	currentIndex = indexOfZeroes[currentIndexOfArray];
	//currentIndexOfArray -= 1;
	//if (currentIndexOfArray < 0)
	//{
	//	cout << "No Solution to Puzzle" << endl;
	//	return false;
	//}
	return true;
}

int SudokuSolver::nextEmpty()
{
	int indexOfRow;
	int indexOfCol;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudokuPuzzle[i][j] == 0)
			{
				indexOfRow = i;
				indexOfCol = j;
				//Convert to a single index number
				int index = indexOfRow * 9 + indexOfCol;
				return index+1;
			}
		}
	}
	return 0;
}

bool SudokuSolver::SolvePuzzle(int maxBackSteps)
{
	//fill indexOfZeroes[] array with the index of all zeroes
	int zeroCount = 0;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudokuPuzzle[i][j] == 0)
			{
				int index = i * 9 + j;
				indexOfZeroes[zeroCount] = index;
				zeroCount++;
			}
		}
	}

	int backStepCount = 0;

	//Start at the index of the first zero in the puzzle
	currentIndexOfArray = 0;
	currentIndex = indexOfZeroes[currentIndexOfArray];
	int indexOfRow;
	int indexOfCol;

	//Stops if puzzle solved or maxBackSteps reached
	while(nextEmpty() != 0 && backStepCount <= maxBackSteps)
	{
		indexOfRow = currentIndex/9;
		indexOfCol = currentIndex%9;
		//cout << "Index Of Current Row:" << indexOfRow << endl;
		//cout << "Index Of Current Column: " << indexOfCol << endl;
		int numIndex = 1; //Numbers we will try to insert
		while(numIndex < 10)
		{
			//Try to insert numIndex at indexOfRow and IndexOfCol position, if == 1 then it was a valid number....... for now... maybe
			if(insert(numIndex,indexOfRow,indexOfCol) == 1)
			{
				//Pushes to stack to keep track of the last numebr we tried in that index of the sudokuPuzzle[][] array
				stack.Push(numIndex);
				//advance to next zero(empty slot in puzzle) 
				currentIndexOfArray = currentIndexOfArray + 1;
				currentIndex = indexOfZeroes[currentIndexOfArray];
				break;
			}
			numIndex++; // increase num to try all 1-9 digits at that slot
			int doAgain = 1;
			//If numIndex reaches 10 that means we tried all 1-9 in that slot and it did not work so we need to backtrack
			if(numIndex == 10)
			{
				while(doAgain == 1)
				{
					goBack(); //backtrack
					indexOfRow = currentIndex/9;
					indexOfCol = currentIndex%9;
					remove(indexOfRow,indexOfCol);
					for(int j = stack.Peek()+1; j < 10; j++) //Start at the last number that didnt work + 1 and check if any other work
					{
						//if insert worked then we have to pop the old number and push the new number
						if(insert(j,indexOfRow,indexOfCol) == 1)
						{
							stack.Pop();
							backStepCount++;
							stack.Push(j);
							//advance to next zero
							currentIndexOfArray = currentIndexOfArray + 1;
							currentIndex = indexOfZeroes[currentIndexOfArray];
							//dont need to backtrack again because number works
							doAgain = 0;
							break;
						}
					}
					//If the number before it doesnt work we do it until we find a possible working number
					//meaning we need to pop() the number that we just tried and doesnt work as well
					if(doAgain == 1)
					{
						stack.Pop();
						backStepCount++;
					}
				}
			}
		}
		//reset the numbers to try
		numIndex = 1;
		if(nextEmpty() == 0)
		{
			cout << "Backsteps: " << backStepCount << endl;
			return true;
		}
	}
	if(backStepCount > maxBackSteps)
	{
		cout << "Backsteps: " << backStepCount << endl;
		return false;
	}
}
void SudokuSolver::DisplayPuzzle()
{
	for (int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cout << sudokuPuzzle[i][j] << " ";
			if(j == 2 || j == 5)
			{
				cout << " ";
			}
		}
		cout << endl;
		if(i == 2 || i == 5)
		{
			cout << endl;
		}
	}
}