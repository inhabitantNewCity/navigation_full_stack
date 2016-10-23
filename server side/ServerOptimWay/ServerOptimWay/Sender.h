#pragma once
#include <map>
class Sender
{
public:
	Sender() {};
	virtual int send(std::map<std::string, int > params, int client_soket) = 0;
	virtual ~Sender();
};