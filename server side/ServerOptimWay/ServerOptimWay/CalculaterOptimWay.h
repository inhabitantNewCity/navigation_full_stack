#pragma once
#include "Listener.h"
class CalculaterOptimWayListener: public Listener 
{
private:
	char* nameBase;

public:
	CalculaterOptimWayListener();
	virtual Coord* calculate(Coord start, Coord finish, int* countVertex);
	~CalculaterOptimWayListener();
};
