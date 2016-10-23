#pragma once

#include <map>
#include "Listener.h"
#include "ListenerImpl.h"

class ListenerFactory
{
private:
	std::map<std::string, Listener*>  listeners;
public:
	 ListenerFactory();
	 Listener* getListenerFormRequest(char request[]);
	 Listener* getDefoultListener();
	 Listener* getLiatenerAtIndex(int i);
	 ~ListenerFactory();
};