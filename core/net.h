#ifndef NET_H
#define NET_H

class Net{
public:
	virtual void* write(void*);
	virtual void* read(void*);
	/*virtual void* accept(void*);
	virtual void* connet(void*);*/
	virtual ~Net();
	virtual void* listen(int port);
};

#endif