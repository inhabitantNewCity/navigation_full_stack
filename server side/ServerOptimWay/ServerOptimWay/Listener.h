#pragma once
#include "Coord.h"
class Listener
{
public:
	Listener() {};
	virtual Coord* calculate(int* countVertex) = 0;
	virtual ~Listener() {};
};