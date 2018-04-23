#ifndef HALL_H 
#define HALL_H 

#include "app.h"
#include "message.h"
#include <boost/lockfree/queue.hpp>

#define MAX_SIZE 1024*8

class Hall : public App{
public:
	virtual ~Hall();
private:
	boost::lockfree::queue<message> mq_(MAX_SIZE);
};

#define 