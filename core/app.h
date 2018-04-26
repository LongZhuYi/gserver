#ifndef APP_H
#define APP_H

class App{
public:
	void init();
	void start();
	void stop();
	void doMsg(void*);
	virtual bool isRuning(){};
	static void * handlerMsg(void *ud);
};

#endif