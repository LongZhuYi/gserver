
#ifndef HALL_H
#define HALL_H

#include "app.h"
#include "msg.h"
#include "script.h"
#include "msg.h"
#include "net.h"

class Hall : public App{
public:
	virtual ~Hall();
private:
	uint   sid_;
	MQ     mq_;
	ENet   en_;
	Script sc_;
	bool running;
	pthread_t pids_[2];
};

#endif