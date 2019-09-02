#pragma once
#include <iostream>
#include <vector>
#include <queue>

class State
{
private:
	void swap(int, int);


	int* currentGrid;
	int getBoard(int *);
	int hWhite(int *) const;
	int hBlack(int *) const;

	int * slideLeft(int, int *, bool, State);
	int * slideRight(int, int *, bool, State);
	int * jumpOneLeft(int, int * board, bool, State);
	int * jumpOneRight(int, int * board, bool, State);
	int * jumpTwoLeft(int, int * board, bool, State);
	int * jumpTwoRight(int, int * board, bool, State);

public:
	State();
	State addState(int *, int, int, int);

	int* nextMoves(int, bool);
	int* board;
	int cost;
	int parent;
	int depth;
	int heuristic(int *) const;

	bool operator==(const State S)const;
	void operator=(const State S);

	void printBoard() const;
};

