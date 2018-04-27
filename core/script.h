#ifndef SCRIPT_H
#define SCRIPT_H

class Script{
public:
	virtual void init(void*){};
	void registry(void*);
	void call(void*, ...);
	void luaAddPath(const char *value);
};

#endif