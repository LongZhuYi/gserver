#ifndef APP_H
#define APP_H

class App{
public:
	void init();
	void start();
	void stop();
	void doMsg(void*);
	virtual void pushMsg(void*)=0;
	virtual bool isRuning()=0;
};

#endif