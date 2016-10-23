#pragma once
#include "Listener.h"
class ListenerImpl
{
public:
	virtual Coord* calculate(Coord start, Coord finish, int* countVertex);
	virtual ~ListenerImpl();
};