#pragma once
#include "Sender.h"
class SenderImpl
{
public:
	SenderImpl();
	virtual int send(std::map<std::string, int > params, int client_soket);
	virtual ~SenderImpl();
};