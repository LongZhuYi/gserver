#ifndef NET_H
#define NET_H

#include "session.h"

class Net{
public:
	virtual void init(void*)=0;
	virtual void listen(int port)=0;
/*	virtual void onRead()=0;
	virtual void onWrite()=0;*/
	virtual void sendMsg(void*,int)=0;
	virtual void* getState()=0;
	virtual void pushSS(Session*)=0;
	virtual void connect(const char*, int)=0;
};

#endif