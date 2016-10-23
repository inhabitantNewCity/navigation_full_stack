#pragma once
#include "Sender.h"
class SenderImpl: public Sender
{
public:
	SenderImpl():Sender(){};
	virtual int send(std::map<std::string, int > params, int client_soket) {
		return 0;
	};
	virtual ~SenderImpl() {};
};