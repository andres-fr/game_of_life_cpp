//============================================================================
// Name           : andresfernandez-5692442_EPR-8-1.cpp
// Author         : Andrés Fernández Rodríguez 
// Matrikelnr.  : 5692442
// Created       : 21-1-2015
// Version        : 1.0
// Description : Einfuehrung in die Programmierung; Blatt 8, Aufgabe 1:
// "Game of life, part 1"
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;

class GameOfLife{
  // interface: as specified
public:
  GameOfLife(int rws, int cols);
  ~GameOfLife();
  void clear();
  void set(int row, int col, int value);
  void set(int row, int col, const char* values);
  int get(int row, int col);
  void print();
  void advance();
private:
  // implementation: store the size of board, declare states
  int columns;
  int rows;
  // 2D-dynamic arrays in the form arr[row][col] = 1 alive, 0 dead
  int** current;
  int** next;
};

// constructor, initializes 2D arrays for current and next state
GameOfLife::GameOfLife(int rws, int cols)
{
  rows = rws;
  columns = cols;
  
  current = new int*[rows];
  for(int i = 0; i < rows; i++)
    current[i] = new int[columns];
 
  next = new int*[rows];
  for(int i = 0; i < rows; i++)
    next[i] = new int[columns];
  // clear: sets all int values to zero
  clear();
}

// destructor: destructs every sub-array and array for current and next
GameOfLife::~GameOfLife()
{
  for(int i = 0; i < rows; i++){
	delete current[i];
	delete next[i];
  }
  delete current;
  delete next; 
}

// initializes to zero the values of current and next
void GameOfLife::clear()
{
  for (int i = 0; i < rows; i++){
	for (int j = 0; j < columns; j++){
	  current[i][j] = 0;
	  next[i][j] = 0;
	}    
  }
}

// assigns value to an specific valid point of current
void GameOfLife::set(int row, int col, int value)
{
  if (row >= 0 && col >= 0 && row < rows && col < columns)
	current[row][col] = value;
}

// iterates over string setting corresponding values to current: 1 alive, 0 dead
void GameOfLife::set(int row, int col, const char* values)
{
  int length = strlen(values);
  int v[length];

  for (int i = 0; i < length; i++)
	{
	  if (values[i] == '.'){v[i] = 0;}
	  else {v[i] = 1;};
	  set(row, col+i, v[i]);
	}
}

// gets value of a valid point, zero if not valid
int GameOfLife::get(int row, int col)
{
  return((row >= 0 && col >= 0 && row < rows && col < columns)?
		 current[row][col] : 0);
}

// prints whole board
void GameOfLife::print()
{
  int cell {-1};
  char output {'X'};
  for (int i = 0; i < rows; i++){
	for (int j = 0; j < columns; j++)
	  {
		  cell = get(i, j);
		  if (cell == 0){output = '.';}
		  else {output = 'O';}
		  cout << output;
	  }cout << endl;
  }
}

// performs the "life" iteration as follows:
void GameOfLife::advance()
{
  // calculate the "neighbours" of each position
  int neighbours {0};
  for (int r = 0; r < rows; r++){
	for (int c = 0; c < columns; c++){
	  neighbours = 0;
	  for (int irow = 0; irow < 3; irow++){
		for (int icol = 0; icol < 3; icol++)
		  {
			if (irow !=1 || icol !=1)neighbours += get(r+irow-1, c+icol-1);
		  } 
	  }
	  // calculate the "next" state based on "neighbours" and the game rules
	  if (neighbours == 3 && current[r][c] == 0) next[r][c] = 1;
	  else if (neighbours < 2 || neighbours > 3) next[r][c] = 0;
	  else next[r][c] = current[r][c];
	}
  }
  // copy the "next" buffer into the "current"
  for (int i = 0; i < rows; i++){
	for (int j = 0; j < columns; j++)
	  {
		current[i][j] = next[i][j];
	  }   
  }
}

// prints initial state, performs and prints "life" iterations
void PlayGameOfLife(GameOfLife& g, int iterations){
  g.print();
  for(int i = 0; i < iterations; ++i)
	{
	  g.advance();
	  cout << endl;
	  g.print();
	}
}

int main()
{
  // instantiate game
  GameOfLife g(10, 10);
  // initialize start-values
  g.set(2, 2, ".O..O.");
  g.set(3, 2, "O.OO.O");
  g.set(4, 2, ".O..O.");
  g.set(5, 2, ".O..O.");
  g.set(6, 2, "O.OO.O");
  g.set(7, 2, ".O..O.");
  // perform and print "life" iterations
  PlayGameOfLife(g, 5);
  return 0;
}





