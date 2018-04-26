#ifndef LUAS_H
#define LUAS_H

#include "conf.h"
#include "script.h"

extern "C"
{	
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
class Luas: public Script {
public:
	void init(void*);
	void registry(void*);
	void loadConfig();
	void call(void* fname, int rid, ...);
private:
	lua_State* state_;

};

#endif