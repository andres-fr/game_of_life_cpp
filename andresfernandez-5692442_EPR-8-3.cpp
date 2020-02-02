//============================================================================
// Name           : andresfernandez-5692442_EPR-8-2.cpp
// Author         : Andrés Fernández Rodríguez 
// Matrikelnr.  : 5692442
// Created       : 22-1-2015
// Version        : 1.0
// Description : Einfuehrung in die Programmierung; Blatt 8, Aufgabe 2:
// "Game of life, part 3"
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;

// helping function, restclass (modulo always positive)
int modulo(int n, int rest){return(((n%rest)>=0)? n%rest : rest+(n%rest));}

// helping class, generates random numbers
class Zufall
{
public:
  Zufall
  (unsigned int anfang);
  unsigned int ziehe_zahl();
private:
  unsigned int x;
};
Zufall::Zufall(unsigned int Startwert){ x = Startwert; }

unsigned int Zufall::ziehe_zahl()
{
  unsigned int a = 16807;
  unsigned int q = 127773, r = 2836, k;
  k = x/q;
  x = a*(x-k*q)-r*k;
  return x;
}

// main class of the game
class GameOfLife
{
  // interface: as specified
public:
  GameOfLife(int rws, int cols);
  ~GameOfLife();
  void clear();
  void set(int row, int col, int value);
  void set(int row, int col, const char* values);
  void set_periodic(bool periodic);
  bool is_periodic();
  int get(int row, int col);
  void print();
  void advance();
  void randomize(Zufall z);
private:
  // implementation: store the size of board, declare states
  int columns;
  int rows;
  // 2D-dynamic arrays in the form arr[row][col] = 1 alive, 0 dead
  int** current;
  int** next;
  // periodic board boolean
  bool m_periodic {false};
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

// destructor: liberates every sub-array and array for current and next
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
  if (m_periodic == false)
	{if (row >= 0 && col >= 0 && row < rows && col < columns)
		current[row][col] = value;
	}
  else current[modulo(row, rows)][modulo(col, columns)] = value;
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

// set the gameboard as periodic or non-periodic
void GameOfLife::set_periodic(bool periodic){m_periodic = periodic;}

// get the value of m_periodic
bool GameOfLife::is_periodic(){return m_periodic;}

// gets value of a point on the table: plain or toroidal
int GameOfLife::get(int row, int col)
{
  if (m_periodic == false)
	{if (row >= 0 && col >= 0 && row < rows && col < columns)
		  return current[row][col];
	  else return 0;
	}
  else return current[modulo(row, rows)][modulo(col, columns)];
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
			if (irow !=1 || icol !=1)
			  {
				neighbours += get(r+irow-1, (c+icol-1));
			  }
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

void GameOfLife::randomize(Zufall z)
{
  int x = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
	  x = z.ziehe_zahl()%2;
	  set(r, c, x);
	}
  }
}

int main()
{
  // instantiate game
  GameOfLife g(12, 60);
  // random initialize start-values
  g.randomize(Zufall(3));
  // perform and print "life" iterations
  PlayGameOfLife(g, 150);
  return 0;
}





