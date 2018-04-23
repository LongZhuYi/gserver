#ifndef APP_H
#define APP_H

class App{
	virtual ~App();
	void* init(void*);
	void* start(void*);
	void* doMsg(void*);
};

#endif