#ifndef _SoLVeR__
#define _SoLVeR__

#include "board.h"

using namespace std;

class Solver: public Board{
	
public:
	Solver(Board& initial);

	int moves();

	vector<Board>* solution();

	bool operator()(Board* b1, Board* b2);

	// variable
	bool isSolvable;

private:
	Board* Goal;
};

#endif
