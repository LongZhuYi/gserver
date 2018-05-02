#ifndef LUAS_H
#define LUAS_H

#include "app.h"
#include "conf.h"
#include "script.h"
#include "timer.h"
#include "mem.h"
#include "hall.h"

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
	void luaAddPath(const char *value);
	void call(const char*, const char*, int rid, ...);

	static int addTick(lua_State* L);
	static int sendMsgToSid(lua_State* L);
private:
	lua_State* state_;
	App* app_;
	int fd_;
};

#endif