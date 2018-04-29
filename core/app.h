#ifndef APP_H
#define APP_H

#include "stdio.h"
#include "stdlib.h"

class App{
public:
	void init();
	void start();
	void stop();
	void doMsg(void*);
	virtual bool isRuning()=0;
	virtual void pushMsg(void*)=0;
	virtual void* getMsg()=0;
	virtual void* getNet()=0;
	virtual void   doTick(long)=0;
};

#endif