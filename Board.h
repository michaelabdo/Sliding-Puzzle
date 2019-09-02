#pragma once
#include "State.h"
#include "compare.h"

class Board
{
private:
	State * currState;
	State * Goal;

	std::priority_queue< State *, std::vector<State *>, compare > gameState;
	std::vector <State *> visited;

	int *goalArr[7];
	int * initGoalArr();

public:
	Board();
	~Board();

	int aStarMeth();
};

