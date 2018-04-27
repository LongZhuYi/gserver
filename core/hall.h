
#ifndef HALL_H
#define HALL_H

#include "app.h"
#include "msg.h"
#include "script.h"
#include "msg.h"
#include "net.h"

class Hall : public App{
public:
	Hall();
	~Hall();
	void init();
	void start();
	void stop();
	void doMsg(void*);
	void pushMsg(void*);
	bool isRuning();
	void* getNet();
	static void* handlerMsg(void*);
private:
	int    sid_;
	MQ     mq_;
	Net*   en_;
	Script* sc_;
	bool running_;
};

#endif