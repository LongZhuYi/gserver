#ifndef LUAS_H
#define LUAS_H

#include "script.h"
#include "lauxlib.h"

class Luas: public Script {
private:
	lua_State* state_;
	
};

#endif