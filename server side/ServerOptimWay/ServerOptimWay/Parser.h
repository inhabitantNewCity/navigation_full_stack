#pragma once
#include "Listener.h"
#include "stdafx.h"
class Parser {
public:
	Parser() {};
	virtual Listener* parsing(char* request, int length) = 0;
	~Parser(){}
};