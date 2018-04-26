#include "luas.h"
#include "lar.h"

#include <cstdio>

void Luas::init(){
	state_ = luaL_newstate();
	luaL_openlibs(state_);

	const char* name = Conf::getStr(std::string("ServerType"));
	const char* path = Conf::getStr(std::string("ScriptPath"));
	const char* init = "init.lua";
	char sp[1024];
	snprintf(sp, sizeof(sp), path, name, init);
	luaL_loadfile(state_, sp);
}

void Luas::registry(void* fs){
	//可以在这里通过luanr向LUA注册需要的类
	Lunar<Lar>::Register(state_);
}

void Luas::call(void* fname, int rid, ...){
	lua_getglobal(state_, "excute");
	lua_pushnumber(state_, rid);
	lua_pushstring(state_, "");
	lua_pcall(state_, 2, 1, 0);
}

void Luas::loadConfig(){
	luaL_loadfile(state_,"config.lua");
}