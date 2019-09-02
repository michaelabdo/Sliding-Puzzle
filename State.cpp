#include "State.h"


State::State()
{
	board = new int[7];

	for (int i = 0; i < 7; i++)
	{
			board[i] = -1;
	}

	cost = 0;
	parent = 0;
	depth = 0;
}

State State::addState(int *ovBoard, int ovCost, int ovPar, int ovDep)
{
	State s;
	s.board = ovBoard;
	s.cost = ovCost;
	s.parent = ovPar;
	s.depth = ovDep;

	return s;
}

void State::printBoard() const
{
	for (int xaxis = 0; xaxis < 7; xaxis++)
	{
			if (board[xaxis] == 0)
				std::cout << " B ";
			else if (board[xaxis] == 1)
				std::cout << " W ";
			else if (board[xaxis] == 2)
				std::cout << " _ ";
	}
		std::cout << std::endl << std::endl;
}

int State::heuristic(int *board) const
{
	return (hWhite(board) + hBlack(board));
}

int State::hWhite(int *board) const
{
	int wFound = 0;			//No Excessive searches
	int hDist = 0;
															//h(n): The number of White tiles on which they have at least
	for (int white = 0; white < 7; white++)					//		one Black tile on their left side.	
	{
		if (this->board[white] == 1)
		{
			wFound++;
			int black = (white - 1);
			if (black < 0)
				goto loop;
			while (black >= 0)
			{
				if (this->board[black] == 0)
				{
					hDist++;
					break;
				}
				black--;
			}
		}
		loop: if (wFound == 3)
			break;
	}

	return hDist;
}

int State::hBlack(int *board) const
{
	int bFound = 0;
	int hDist = 0;
															//h'(n): The sum of the number of White tiles on each Black
	for (int black = 0; black < 7; black++)					//		 tile's right side.	
	{
		if (this->board[black] == 0)
		{
			bFound++;
			int white = (black + 1);
			if (white > 6)
				goto loop;
			while (white < 7)
			{
				if (this->board[white] == 1)
					hDist++;
				
				white++;
			}
		}
		loop: if (bFound == 3)
			break;
	}

	return hDist;
}

int State::getBoard(int * board)
{
	return *board;
}

bool State::operator==(const State S)const
{
	for (int xaxis = 0; xaxis < 7; xaxis++)
	{
			if (this->board[xaxis] != S.board[xaxis])
			{
				return 0;
			}
	}
	return 1;
}

void State::operator=(const State S)
{
	for (int xaxis = 0; xaxis < 7; xaxis++)
	{
			this->board[xaxis] = S.board[xaxis];
	}
}

void State::swap(int x, int x2)
{
	int temp = this->board[x];
	this->board[x] = this->board[x2];
	this->board[x2] = temp;
}

int * State::nextMoves(int move, bool addDepth)
{
	State curState;
	for (int i = 0; i < 7; i++)
			curState.board[i] = this->board[i];

	for (int i = 0; i < 7; i++)
	{
		if (board[i] == 2)
		{
			if (move == 0 && i > 0)
				slideLeft(i, board, addDepth, curState);
			if (move == 1 && i < 6)
				slideRight(i, board, addDepth, curState);
			if (move == 2 && i > 1)
				jumpOneLeft(i, board, addDepth, curState);
			if (move == 3 && i < 5)
				jumpOneRight(i, board, addDepth, curState);
			if (move == 4 && i > 2)
				jumpTwoLeft(i, board, addDepth, curState);
			if (move == 5 && i > 4)
				jumpTwoRight(i, board, addDepth, curState);
		}
	}

	return curState.board;

}

int * State::slideLeft(int index, int * board, bool addDepth, State s)		//Slide and Swap Move
{
	if (index > 0)
	{
		s.swap(index, index - 1);
		if (addDepth)
			depth++;
	}
	return board;
}

int * State::slideRight(int index, int * board, bool addDepth, State s)		//Slide and Swap Move
{
	if (index < 6)
	{
		s.swap(index, index + 1);
		if (addDepth)
			depth++;
	}
	return board;
}

int * State::jumpOneLeft(int index, int * board, bool addDepth, State s)		//Jump one and Swap Move
{
	if (index > 1)
	{
		s.swap(index, index - 2);
		if (addDepth)
			depth = depth + 2;
	}
	return board;
}

int * State::jumpOneRight(int index, int * board, bool addDepth, State s)		//Jump one and Swap Move
{
	if (index < 5)
	{
		s.swap(index, index + 2);
		if (addDepth)
			depth = depth + 2;
	}

	return board;
}

int * State::jumpTwoLeft(int index, int * board, bool addDepth, State s)		//Jump Two and Swap Move
{
	if (index > 2)
	{
		s.swap(index, index - 3);
		if (addDepth)
			depth = depth + 3;
	}

	return board;
}

int * State::jumpTwoRight(int index, int * board, bool addDepth, State s)		//Jump Two and Swap Move
{
	if (index < 4)
	{
		s.swap(index, index + 3);
		if (addDepth)
			depth = depth + 3;
	}
	return board;
}
