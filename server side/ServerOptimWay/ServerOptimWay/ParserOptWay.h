#pragma once
#include "Parser.h"
#include "ListenerImpl.h"
class ParserOptWay : public Parser {
public:
	ParserOptWay() :Parser() {};
	Listener* parsing(char* request, int length) {
		Coord start;
		Coord finish;
		char* namebase;
		int* n;
			//todo: parsing
		return new ListenerOptimWay(start, finish, namebase);
	};
	~ParserOptWay(){}

};