#include "Board.h"


Board::Board()
{
	currState = new State();
	int* goalArr = initGoalArr();

	std::cout << "Enter numbers 0 to 8 in any order: \n";

	int * grid = new int [7];
	
	
	grid[0] = 0;
	grid[1] = 0;
	grid[2] = 0;
	grid[3] = 2;
	grid[4] = 1;
	grid[5] = 1;
	grid[6] = 1;
	
	/*
	grid[0] = 1;
	grid[1] = 1;
	grid[2] = 1;
	grid[3] = 2;
	grid[4] = 0;
	grid[5] = 0;
	grid[6] = 0;
	*/

	std::cout << "Initial State: \n";
	*currState = currState->addState(grid, 0, 0, 0);
	currState->printBoard();
	//currState->heuristic(grid);


	Goal = new State();
	std::cout << "Goal State: \n";
	*Goal = Goal->addState(goalArr, -1, -1, -1);
	Goal->printBoard();
}

Board::~Board()
{
	delete Goal;
	delete currState;
}

int * Board::initGoalArr()
{
	int * retArr = new int [7];

	retArr[0] = 1;		//1 = White
	retArr[1] = 1;
	retArr[2] = 1;
	retArr[3] = 2;		//2 = Empty
	retArr[4] = 0;		
	retArr[5] = 0;
	retArr[6] = 0;		//0 = Black


	return retArr;
}

int Board::aStarMeth()
{
	bool contains = false;
	int depth = -1, temp, steps = 0;

	if (*currState == *Goal)
	{
		std::cout << "found!\n\n";

		currState->printBoard();
		return 0;
	}

	State * current = new State, *child = new State;
	gameState.push(currState);

	while (!gameState.empty())
	{
		current = gameState.top();
		visited.push_back(current);
		gameState.pop();

		if (*current == *Goal)			//Goal Test
		{
			std::cout << "Goal State Found!\n\n";
			temp = current->depth;
			std::cout << "Cost : " << current->cost << std::endl;
			current->printBoard();


			std::cout << "Previous States: \n\n";
			while (1)
			{
				steps++;
				std::cout << "Step(s): " << steps << std::endl;
				visited[current->parent]->printBoard();
				current = visited[current->parent];


				if ((*current == *currState))
					break;
			}
			return temp;
		}

		for (int i = 0; i < 7; i++)			//For each move
		{
			child = new State;
			child->board = current->nextMoves(i, true);
			child->cost = Goal->heuristic(current->nextMoves(i, false)) + current->depth; // f(n) = h(n) + g(n)
			child->parent = depth + 1;
			child->depth = current->depth;

			for (std::vector<State *>::iterator it = visited.begin(); it != visited.end(); ++it)		//Iterates through 'visited' vector
			{
				if (*(*it) == *child)
				{
					contains = true;
					if (child->cost >= (*it)->cost)						//overwrites node with better path 
						break;
					else
					{
						(*it)->cost = child->cost;
						(*it)->parent = child->parent;
					}
				}
			}
			if (contains == false)
				gameState.push(child);
			contains = false;
		}
		depth++;
	}
	return depth;
}

