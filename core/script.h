#ifndef SCRIPT_H
#define SCRIPT_H

class Script{
	virtual void init(void*);
	virtual void registry(void*);
	virtual void call(void*, ...);
};

#endif