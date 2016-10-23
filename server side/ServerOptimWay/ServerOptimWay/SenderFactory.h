#pragma once
#include <vector>
#include "Sender.h"
#include "SenderImpl.h"
class SenderFactory
{
private:
	std::vector<Sender*>  senders;
public:
	SenderFactory() {
		senders[0] = new SenderImpl();
	};
	Sender* getDefoultSender() {
		return senders[0];
	};
	Sender* getSenderAtIndex(int i) {
		return senders[i];
	};
	~SenderFactory() {
		senders.~vector();
	};
};