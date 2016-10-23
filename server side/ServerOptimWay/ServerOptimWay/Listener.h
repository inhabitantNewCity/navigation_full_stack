#pragma once
#include "Coord.h"
class Listener
{
public:
	virtual Coord* calculate(Coord start, Coord finish, int* countVertex) = 0;
	virtual ~Listener();
};