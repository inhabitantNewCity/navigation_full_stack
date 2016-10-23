#pragma once

#include <map>
#include <functional>
#include "Parser.h"
#include "ParserOptWay.h"
using namespace std;

class ListenerFactory
{
private:
	map<string, Parser*>  parsers;
public:
	ListenerFactory() {
		Parser* parser = new ParserOptWay();
		parsers["optWay"] = parser;
	};
	Listener* getListenerFormRequest(char request[]){
		string title = request;
		// todo parsing title from request
		return parsers[title.substr(0, 5)]->parsing(request, max_client_buffer_size);
	};
	~ListenerFactory() {
		delete[]parsers["optWay"];
	};
};