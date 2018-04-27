#ifndef NET_H
#define NET_H

class Net{
public:
	virtual void init(void*)=0;
	virtual void listen(int port)=0;
	virtual void onRead()=0;
	virtual void onWrite()=0;
	virtual void* getState()=0;
};

#endif