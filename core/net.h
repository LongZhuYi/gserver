#ifndef NET_H
#define NET_H

class Net{
public:
	virtual void  init();
	virtual void* write(void*);
	virtual void* read(void*);
	/*virtual void* accept(void*);
	virtual void* connet(void*);*/
	virtual void* dispatch();
	virtual ~Net();
	virtual void listen(int port);
};

#endif