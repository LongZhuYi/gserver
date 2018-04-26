#ifndef NET_H
#define NET_H

class Net{
public:
	virtual void  init(void*){};
	void* write(void*);
	void* read(void*);
	void* dispatch();
	void listen(int port);
};

#endif