#include "luas.h"
#include "lar.h"
#include "log.h"

#include <cstdio>
#include <string>

void Luas::init(void* ){
	state_ = luaL_newstate();
	luaL_openlibs(state_);

	luaAddPath(std::string("../script/?.lua").c_str());

	const char* name = Conf::single()->getStr(std::string("stype"));
	const char* spath = Conf::single()->getStr(std::string("spath"));
	std::string path(spath);
	path.append(name);
	path.append("/");
	path.append("init.lua");
	luaL_loadfile(state_, path.c_str());
	int result = lua_pcall(state_, 0, 0, 0);
	//LOG("%s", "Luas::init")
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

void Luas::luaAddPath(const char* value) {
	const char* name = "path";
	std::string v;
	lua_getglobal(state_, "package");
	lua_getfield(state_, -1, name);
	v.append(lua_tostring(state_, -1));
	v.append(";");
	v.append(value);
	lua_pushstring(state_, v.c_str());
	lua_setfield(state_, -3, name);
	lua_pop(state_, 2);
}

/*
    v.append(lua_tostring(ls, -1));  
    v.append(";");  
    v.append(value); 
*/