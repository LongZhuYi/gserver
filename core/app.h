#ifndef APP_H
#define APP_H

class App{
	virtual ~App();
	void init();
	void start();
	void stop();
	void doMsg(void*);
	bool isStop();
	static void * handlerMsg(void *ud);
};

#endif