#include "luas.h"

void Luas::init(){
	state_ = luaL_newstate();
	luaL_loadfile(state_,"init.lua");
	lua_pcall(state_,0,0,0);
}

void Luas::registry(void* fs){
	
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