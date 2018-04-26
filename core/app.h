#ifndef APP_H
#define APP_H

class App{
public:
	virtual ~App();
	void init();
	void start();
	void stop();
	void doMsg(void*);
	bool isRuning();
	static void * handlerMsg(void *ud);
};

#endif