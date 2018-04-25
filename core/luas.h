#ifndef LUAS_H
#define LUAS_H

#include "script.h"
extern "C"
{	
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
class Luas: public Script {
public:
	void loadConfig();
private:
	lua_State* state_;

};

#endif