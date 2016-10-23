#pragma once
#include "Sender.h"
#include "SenderImpl.h"
class SenderFactory
{
private:
	std::map<std::string, Sender*>  listeners;
public:
	SenderFactory();
	Sender* getDefoultSender();
	Sender* getSenderAtIndex(int i);
	~SenderFactory();
};