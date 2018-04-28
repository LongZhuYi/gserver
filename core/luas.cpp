#include "hredis.h"
#include "luas.h"
#include "lar.h"
#include "log.h"

#include <cstdio>
#include <string>
#include <sstream>

int pcall_callback_err_fun(lua_State* L);

void Luas::init(void* ){
	state_ = luaL_newstate();
	luaL_openlibs(state_);
	registry(NULL);

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
	printf("Luas::init result %d\n", result);
}

void Luas::registry(void* fs){
	//可以在这里通过luanr向LUA注册需要的类
	Lunar<Lar>::Register(state_);
	Lunar<HRedis>::Register(state_);
}

void Luas::call(const char* str, int rid, ...){
	//lua_pushcfunction(state_, pcall_callback_err_fun);
	//int pos_err = lua_gettop(state_);

	lua_getglobal(state_, "excute");
	lua_pushstring(state_, str);
	lua_pushnumber(state_, rid);
	int res = lua_pcall(state_, 2, 0, 0);
	if(res !=0){
		int t = lua_type(state_, -1);  
        const char* err = lua_tostring(state_,-1);  
        printf("Error: %s\n", err);  
        lua_pop(state_, 1);
	}
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

int pcall_callback_err_fun(lua_State* L)  
{  
    lua_Debug debug= {};  
    int ret = lua_getstack(L, 2, &debug);
    lua_getinfo(L, "Sln", &debug);  
    std::string err = lua_tostring(L, -1);  
    lua_pop(L, 1);  
    std::stringstream m;  
    m << debug.short_src << ":line " << debug.currentline;  
    if (debug.name != 0) {  
        m << "(" << debug.namewhat << " " << debug.name << ")";  
    }
    m << " [" << err << "]";  
    lua_pushstring(L, m.str().c_str());  
    return 1;  
}  