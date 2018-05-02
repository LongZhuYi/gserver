
#ifndef HALL_H
#define HALL_H

#include "app.h"
#include "msg.h"
#include "script.h"
#include "msg.h"
#include "net.h"
#include "timer.h"

class Hall : public App{
public:
	Hall();
	~Hall();
	void init(const char*, int, int);
	void start();
	void stop();
	void doMsg(void*);
	void pushMsg(void*);
	bool isRuning();
	void* getNet();
	void* getMsg();
	void   doTick(long id);
	//void   sendMsgToSid(void*);
	static void* handlerMsg(void*);

	const char* getSType();
	MQ     mq_;
private:
	const char* sName_;
	int port_;
	int    sid_;
	Timer* tm_;
	Net*   en_;
	Script* sc_;
	bool running_;
};

#endif