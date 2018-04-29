#ifndef SCRIPT_H
#define SCRIPT_H

class Script{
public:
	virtual void init(void*){};
	void registry(void*);
	virtual void call(const char*, const char*, int rid, ...)=0;
	void luaAddPath(const char *value);
};

#endif