#pragma once

#include <thread>
#include <mutex>
#include <vector>

#include "ListenersFactory.h"
#include "Sender.h"
#include "SenderFactory.h"
#include "ServletImpl.h"


class Servlet;
class ServletFactory;
class ThreadPool
{
private:


	ServletFactory* factory;
	int countThreads;
	int countWorkingThreads;

	std::recursive_mutex insert_mutex;
	std::recursive_mutex get_mutex;
	std::vector<std::thread> workingThreads;

public:
	ThreadPool(int countThreads = 1); 

	int startThreds(char buf[], int client_soket);

	int endThreds(Servlet* task);

	~ThreadPool();
};


class Servlet
{
protected:
	Listener* listener;
	ListenerFactory* listenerFactory;

	Sender* sender;
	SenderFactory* senderFactory;

	ThreadPool* pool;
public:
	Servlet(ThreadPool* pool) {
		listenerFactory = new ListenerFactory();
		senderFactory = new SenderFactory();
	};
	virtual Coord* handeling(char buf[], int client_soket) = 0;
	virtual ~Servlet();
};


class ServletImpl : public Servlet
{
public:
	ServletImpl(ThreadPool* pool) : Servlet(pool) {};
	virtual Coord* handeling(char buf[], int client_soket) {
		listener = listenerFactory->getListenerFormRequest(buf);
		//todo: parse parameters and call calculate method
		
		sender = senderFactory->getDefoultSender();
		//todo edit send method for sending cord or vripe result in map
		
		pool->endThreds(this);
	};
	virtual ~ServletImpl();
};

class ServletFactory {
public:
	ServletFactory();
	Servlet* getDefoultServlet(ThreadPool* pool) {
		return new ServletImpl(pool);
	};
	Servlet* getSenderAtIndex(ThreadPool* pool, int i);
	~ServletFactory();
};



ThreadPool::ThreadPool(int countThreads) {
	this->countThreads = countThreads;

	factory = new ServletFactory();
	countWorkingThreads = 0;
}
int ThreadPool::startThreds(char buf[], int client_soket) {
	while (countWorkingThreads == countThreads)
		;

	Servlet* servlet = factory->getDefoultServlet(this);
	std::thread current_thread([&servlet, buf, client_soket]() { servlet->handeling(buf, client_soket); });
	current_thread.detach();
	insert_mutex.lock();
		workingThreads.push_back(current_thread);
		countWorkingThreads++;
	insert_mutex.unlock();
	return 0;
}


int ThreadPool::endThreds(Servlet* task) {
	get_mutex.lock();
		delete[] task;
		countWorkingThreads--;
	get_mutex.unlock();
	return 0;
}

