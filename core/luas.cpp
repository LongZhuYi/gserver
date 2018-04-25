#include "luas.h"
#include "lar.h"

void Luas::init(){
  state_ = luaL_newstate();
  luaL_openlibs(L);
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