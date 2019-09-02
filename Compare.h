#pragma once
#include "State.h"

class compare {
public:
	bool operator()(State * n1, State * n2)const {
		return n1->cost > n2->cost;
	}
};
