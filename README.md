# Sudoku

Code that will solve Sudoku puzzles.

# Making a Sudoku board class

In the file `Sudoku.h` is a class `Sudoku` that holds an *incomplete* [Sudoku](https://en.wikipedia.org/wiki/Sudoku) solution.

It has a constructor that takes a single argument -- the size of the board.  For instance, for a 9x9 Sudoku, the constructor would be given the value 9.

I store the incomplete solution as a member variable. The *recommended* way to do this is to have a vector of vectors (a square array), in which each square is represented as a `set<int>` that holds the values that could possibly go in that square. Initially, for a 9x9 Sudoku, if the grid is completely blank, each set will contain the values `{1,2,3,4,5,6,7,8,9}`. When a square is given some value, the set is cleared and replaced with a set containing just that one value -- the other options are removed.

The function `getSquare(int row, int col)` returns the value in the cell in the square at the given row and column:

- If there is only one value in the set for that square, return the number in that set.
- Otherwise, return -1 (a dummy value to indicate we don't know what should be in that square yet)

# Setting the value of a Sudoku square

The function `setSquare(int row, int col, int value)` sets the value in the cell in the square at the given row and column, then updates the sets of possible values in the rest of the grid to remove choices that have been eliminated. For instance, if we put a '3' on a given row, then nothing else on that row can have the value 3.

The implementation of setSquare is split into two parts.

First, the easy part: the set of possible values for that cell is cleared, and `value` is inserted. This forces that cell to have that value.

Then, a loop begins that does the following:

- Loop over the entire grid
- For each square that has only one value in it, remove that value from the sets of possible values for:
    - All the other squares on that row
    - All the other squares in that column
    - All the other squares in the same *box*.  A 9x9 grid is divided into 9 boxes, each 3x3: no two values in the same box can have the same value.  For larger grids (e.g. 16x16), the size of the box is always the square root of the size of the grid.
 

If at any point the set of values for a square becomes empty, the function returns false: it has been shown that there is no value that can go in a square.

This process stops when, having looped over the board, and updated the sets by removing values, our sets have stopped getting any smaller.  At this point the function returns true.

For simple Sudodu puzzles, this process here is enough to solve the puzzle.  No guesswork is needed: setting the squares of the board to hold the initial values specified in the puzzle is enough to cause all the other squares of the board to have only one option left.

## Usage

You can test this by compiling and running BasicSudoku.cpp.

This calls `setSquare` for the values in a simple Sudoku puzzle; then uses `getSquare` to check the code has the right answer.  

# Searching for a solution

For more complex puzzles, after putting in the initial values using setSquare, some of the squares on the board have more than one value left in their set of possible values -- using logic alone, we cannot deduce what the value has to be; we have to make a guess and see what happens.

For this, we are going to use the Searchable class.  This is an *abstract class* for puzzles, containing the following virtual functions:

- `isSolution()`: this returns true if the puzzle has been solved.  For Sudoku, this means all the squares contain just one value.
- `write(ostream & o)`: a debugging function to print the board to screen.
- `heuristicValue()`: an estimate of how far the puzzle is from being solved. 
- `successors()`: in a situation where a guess is needed, this returns several new puzzle objects, each of which corresponds to a different guess having been made.

The Sudoku class inherits from Searchable by changing the opening of the class definition to `class Sudoku : public Searchable`

isSolution() only returns true if the puzzle has been solved; i.e. every set in every square is of size 1.

write() prints the board one row at a time:

- If the square has more than one value in its set, print a space character
- Otherwise, print the value from the set.

successors() returns a vector of successors.

## Usage

You can test the code for these functions by compiling and running BreadthFSSudoku.cpp.

## Better search with a heuristic

`BreadthFirstSearch.h` defines a search strategy known as breadth-first search.  It has a queue of incomplete solutions (initially, the starting configuration of the board.  Then, it repeatedly takes a board off the queue, and if it's not a solution, gets its successors, and puts them on the queue.

The queue used follows a `first in, first out` (FIFO) strategy: the next board is always taken off the front of the queue; and new boards are always put on the back of the queue.

Breadth-first search can be improved by using a heuristic: an estimate of how close a board is to being finished.  The `Searchable` class defines a `heuristicValue()` function that calculates an estimate of this.

The `heuristicValue()` function returns the number of squares on the board whose sets are of size greater than 1.  On paper this corresponds to the number of squares we haven't written a number into yet; and the fewer the squares, the closer it looks like that board is to being a solution.

Instead of using a first-in first-out queue (as in breadth-first search) the `BestFirstSearch` class uses a priority queue, sorted in ascending order of heuristic value.  That is, when we get the successors to a board, these are inserted into the queue so that the board with the smallest heuristic value is always at the front.

## Usage

To test this code, compile and run BestFSSudoku.cpp. This should expand fewer nodes than breadth-first search.
