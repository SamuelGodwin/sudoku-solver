#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

#include <set>
#include <math.h>       // sqrt
using namespace std;

#include <iostream>     // std::cout, std::ostream, std::ios

class Sudoku {

public://cout every step of the logic then walk through the steps in cmd

	vector<vector<set<int> > > sudokuBoard; // each square in the matrix can contain e.g. 1-9
	int sizeOfBoard;

	// if grid is blank, each SET will contain {1,2,3,4,5,6,7,8,9}.
	// when a square is GIVEN some value, that set is cleared and replaced with
	// e.g. {,,3,,,,,,}--the other options are removed.

	// can't have sizeOfBoard as an odd number ?? (with regards to sqrt?) //is 9x9 the MINIMUM?
	Sudoku(int sizeOfBoardIn) // sizeOfBoard i.e. 9 for 9x9. make sure it can only be a number that can be square rooted
	: sizeOfBoard(sizeOfBoardIn) {
		cout << "constructorrrr\n";
		for (int x = 0; x < sizeOfBoard; x++) {
			vector<set<int>> vectorOfSets;
			for (int y = 0; y < sizeOfBoard; y++) {
				set<int> set;
				for (int i = 1; i <= sizeOfBoard; i++){
					set.insert(i);
				}
				vectorOfSets.push_back(set);
			}
			sudokuBoard.push_back(vectorOfSets);

		}
		cout << "Board filled (constructor finished)\n";
	}

	// returns the value in the cell in the square at the given row and column:
	int getSquare(int row, int col) {
	    //If there is only one value in the set for that square, return the number in that set.
		cout << "size checked in if statement for row " << row << ", column " << col << " is: " << sudokuBoard[row][col].size() << "\n";

		cout << "Set contents: [";
		for (auto set : sudokuBoard[row][col])
		{
			cout << set << ' ';
		}
		cout <<"]\n";


		if (sudokuBoard[row][col].size() == 1) { // size of set at row,col
			//set s = sudokuBoard[row][col]
			return *sudokuBoard[row][col].begin(); //the value pointed to by the set iterator at this square (first & only element).
		}


	    //Otherwise, return -1 (a dummy value to indicate we don't know what should be in that square yet)
		return -1;

	}

	bool setSquare(int row, int col, int value) {

		cout << "before setSquare\n";

		//sets the value in the cell (in the square at the given row and column),
		sudokuBoard[row][col].clear();
		sudokuBoard[row][col].insert(value); // would need a check ensuring it is the correct value.
		//then updates the sets of possible values in the rest of the grid to remove choices that have been eliminated.
		//For instance, if we put a '3' on a given row, then nothing else on that row can have the value 3.
		bool repeat = true;

		//while(repeat = true) {

			repeat = false;
			cout << "\nRUNS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n";



			/*//for (int x = 0; x != sizeOfBoard; ++x) {
				//for (int y = 0; y!= sizeOfBoard; ++y) {
					cout << "[";
					for (auto set : sudokuBoard[row][col])
					{
						cout << set << ' ';
						//cout << "YO";
					}
					cout <<"]";
				//}
			//}
			cout << "\n";*/


			for (int x = 0; x != sizeOfBoard; ++x) {
				for (int y = 0; y!= sizeOfBoard; ++y) {

					if (sudokuBoard[x][y].size() == 1) { //if the set in the inner vector is of size 1


						//cout << "before column\n";

						// other items in the DOWNWARDS (column)
						for (int iRemovalBeforePos = 0; iRemovalBeforePos < y; iRemovalBeforePos++) {


							auto valueItr = sudokuBoard[x][iRemovalBeforePos].find(*sudokuBoard[x][y].begin());

							if (valueItr != sudokuBoard[x][iRemovalBeforePos].end()) { // if rest of this row also contains that element?

								cout << "\nBEFORE REMOVAL IN COLUMN FOR " << x << " " << iRemovalBeforePos << " [";
								for (auto set : sudokuBoard[x][iRemovalBeforePos])
								{
									cout << set << ' ';
								}
								cout <<"]\n";

								cout << "erasing valueItr value: " << *valueItr;

								sudokuBoard[x][iRemovalBeforePos].erase(valueItr);

								cout << "\nAFTER REMOVAL IN COLUMN FOR " << x << " " << iRemovalBeforePos << " [";
								for (auto set : sudokuBoard[x][iRemovalBeforePos])
								{
									cout << set << ' ';
								}
								cout <<"]\n\n";

								repeat = true;
								if (sudokuBoard[x][iRemovalBeforePos].empty()) {
									return false;
								}
							}
						}

						for (int iRemovalAfterPos = y + 1; iRemovalAfterPos < sizeOfBoard; iRemovalAfterPos++) {
							auto valueItr = sudokuBoard[x][iRemovalAfterPos].find(*sudokuBoard[x][y].begin());
							if (valueItr != sudokuBoard[x][iRemovalAfterPos].end()) { // if rest of this row also contains the element

								cout << "\nBEFORE REMOVAL IN COLUMN FOR " << x << " " << iRemovalAfterPos << " [";
								for (auto set : sudokuBoard[x][iRemovalAfterPos])
								{
									cout << set << ' ';
								}
								cout <<"]\n";

								cout << "erasing valueItr value: " << *valueItr;

								sudokuBoard[x][iRemovalAfterPos].erase(valueItr);

								cout << "\nAFTER REMOVAL IN COLUMN FOR " << x << " " << iRemovalAfterPos << " [";
								for (auto set : sudokuBoard[x][iRemovalAfterPos])
								{
									cout << set << ' ';
								}
								cout <<"]\n\n";

								repeat = true;
								if (sudokuBoard[x][iRemovalAfterPos].empty()) {
									return false;
								}
							}
						}

						//cout << "before row\n";

						// other items in the ACROSS (row)
						//needs to keep the current row position but check that row position at each of the other columns
						for (int iRemovalBeforePos = 0; iRemovalBeforePos < x; iRemovalBeforePos++) {
							auto valueItr = sudokuBoard[iRemovalBeforePos][y].find(*sudokuBoard[x][y].begin());
							if (valueItr != sudokuBoard[iRemovalBeforePos][y].end()) { // if rest of this row also contains that element?

								cout << "\nBEFORE REMOVAL IN ROW FOR " << iRemovalBeforePos << " " << y << " [";
								for (auto set : sudokuBoard[iRemovalBeforePos][y])
								{
									cout << set << ' ';
								}
								cout <<"]\n";

								cout << "erasing valueItr value: " << *valueItr;

								sudokuBoard[iRemovalBeforePos][y].erase(valueItr);

								cout << "\nAFTER REMOVAL IN ROW FOR " << iRemovalBeforePos << " " << y << " [";
								for (auto set : sudokuBoard[iRemovalBeforePos][y])
								{
									cout << set << ' ';
								}
								cout <<"]\n\n";


								repeat = true;
								if (sudokuBoard[iRemovalBeforePos][y].empty()) {

									return false;
								}
							}
						}

						for (int iRemovalAfterPos = x + 1; iRemovalAfterPos < sizeOfBoard; iRemovalAfterPos++) {
							auto valueItr = sudokuBoard[iRemovalAfterPos][y].find(*sudokuBoard[x][y].begin());
							if (valueItr != sudokuBoard[iRemovalAfterPos][y].end()) { // if rest of this row also contains the element

								cout << "\nBEFORE REMOVAL IN ROW FOR " << iRemovalAfterPos << " " << y << " [";
								for (auto set : sudokuBoard[iRemovalAfterPos][y])
								{
									cout << set << ' ';
								}
								cout <<"]\n";

								cout << "erasing valueItr value: " << *valueItr;

								sudokuBoard[iRemovalAfterPos][y].erase(valueItr);

								cout << "\nAFTER REMOVAL IN ROW FOR " << iRemovalAfterPos << " " << y << " [";
								for (auto set : sudokuBoard[iRemovalAfterPos][y])
								{
									cout << set << ' ';
								}
								cout <<"]\n\n";

								repeat = true;
								if (sudokuBoard[iRemovalAfterPos][y].empty()) {
									cout << "FAILED BECAUSE " << iRemovalAfterPos << " " << y << " contains nothing" ;
									return false;
								}
							}
						}
						//setsquare
						//row delete
						//column delete
						//box delete

						cout << "before box\n";

						//other items in the BOX







						//first row value of local box:
						int firstLocalX = (row / ((sqrt(sizeOfBoard))*sqrt(sizeOfBoard)) );//cast division to an int for integer division (there might be a better way)

						//cout<< "ROW IS: " << firstLocalX << "\n";

						cout<< "FIRST LOCAL X IS: " << firstLocalX << "\n";


						//first col value of local box:

						int firstLocalY = (col / (sqrt(sizeOfBoard)*sqrt(sizeOfBoard)) ); //cast division to an int for integer division (there might be a better way)
						//last row value of local box:
						int lastLocalX = (firstLocalX + sqrt(sizeOfBoard) - 1);
						//last col value of local box:
						int lastLocalY = (firstLocalY + sqrt(sizeOfBoard) - 1);

						for (int xLocal = firstLocalX; xLocal <= lastLocalX ; xLocal++) {
							for (int yLocal = firstLocalY; yLocal <= lastLocalY ; yLocal++) {

								if (sudokuBoard[xLocal][yLocal] != sudokuBoard[x][y]) { //square being checked is NOT same square as the square with only 1 value
									cout<< "Doing a box delete, because it was found that " << x << " " << y << " Contained: " << *sudokuBoard[x][y].begin() << "\n";
									auto valueItr = sudokuBoard[xLocal][yLocal].find(*sudokuBoard[x][y].begin());
									if (valueItr != sudokuBoard[xLocal][yLocal].end()) { // if contains the element to be removed
										cout << "\nBEFORE REMOVAL IN BOX FOR " << xLocal << " " << yLocal << " [";
										for (auto thing : sudokuBoard[xLocal][yLocal])
										{
											cout << thing << ' ';
										}
										cout <<"]\n";

										cout << "erasing valueItr value: " << *valueItr;

										sudokuBoard[xLocal][yLocal].erase(valueItr);

										cout << "\nAFTER REMOVAL IN BOX FOR " << xLocal << " " << yLocal << " [";
										for (auto thing : sudokuBoard[xLocal][yLocal])
										{
											cout << thing << ' ';
										}
										cout <<"]\n";

										repeat = true;
										if (sudokuBoard[xLocal][yLocal].empty()) {

											return false;
										}
									}
								}
							}
						}





					}
				}
			}
		//}

		/*for (int x = 0; x != 2; ++x) {
			for (int y = 0; y!= 2; ++y) {
				cout << "size checked in if statement for row " << x << ", column " << y << " is: " << sudokuBoard[x][y].size() << "\n";

				cout << "Set contents of (" << x << ", " << y << ") is: " ;
				for (auto set : sudokuBoard[x][y])
				{
					cout << set << ' ';
				}
				cout <<"\n";
			}
		}
		cout << "\n";*/

		/*for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				//cout << "size checked in if statement for row " << x << ", column " << y << " is: " << sudokuBoard[x][y].size() << "\n";

				cout << "Set contents of (" << x << ", " << y << ") is: " ;
				for (auto set : sudokuBoard[x][y])
				{
					cout << set << ' ';
				}
				cout <<"\n";
			}
		}*/

		//get rid of the while for looping all squares
		//couts



		return true;

	}

};



#endif
