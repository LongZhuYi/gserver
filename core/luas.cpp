#include "luas.h"
#include "lar.h"

#include <cstdio>

void Luas::init(){
	state_ = luaL_newstate();
	luaL_openlibs(L);

	char* name = Conf:getStr("ServerType");
	char* path = Conf:getStr("ScriptPath")

	char sp[1024];
	snprintf("%s\\%s\\init.lua", sizeof(sp), path, name);
	luaL_loadfile(sp);
}

void Luas::registry(void* fs){
	//可以在这里通过luanr向LUA注册需要的类
	Lunar<Lar>::Register(state_);
}

void Luas::call(void* fname, rid, ...){
	lua_getglobal(state_, "excute");
	lua_pushnumber(state_, rid);
	lua_pushstring(state_, "");
	lua_pcall(state_, 2, 1, 0);
}

void Luas::loadConfig(){
	luaL_loadfile(state_,"config.lua");
}