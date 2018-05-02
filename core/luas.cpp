#include "hredis.h"
#include "luas.h"
#include "lar.h"
#include "log.h"

#include <cstdio>
#include <string>
#include <sstream>

int pcall_callback_err_fun(lua_State* L);

void Luas::init(void* ud){
	app_ = (App*)(ud);
	state_ = luaL_newstate();
	luaL_openlibs(state_);
	registry(NULL);

	luaAddPath(std::string("../script/?.lua").c_str());
	const char* name = app_->getSType();
	const char* spath = Conf::single()->getStr(std::string("spath"));
	std::string path(spath);
	path.append(name);
	path.append("/");
	path.append("main.lua");
	luaL_loadfile(state_, path.c_str());
	int result = lua_pcall(state_, 0, 0, 0);
	if(result != 0){
		int t = lua_type(state_, -1);  
		const char* err = lua_tostring(state_,-1);  
		printf("Error: %s\n", err);  
		lua_pop(state_, 1);
	}
	//printf("Luas::init result %d %s\n", result, path.c_str());
}

void Luas::registry(void* fs){
	//可以在这里通过luanr向LUA注册需要的类
	Lunar<Lar>::Register(state_);
	Lunar<HRedis>::Register(state_);
	lua_register(state_, "addTick", Luas::addTick);
}

void Luas::call(const char* fName, const char* str, int rid, ...){
	lua_getglobal(state_, fName);
	assert(lua_isfunction(state_, 1));
	lua_newtable(state_);
	lua_pushstring(state_, "msg");
	lua_pushstring(state_, str);
	lua_settable(state_, -3);

/*	lua_pushstring(state_, "id");
	lua_pushnumber(state_, rid);
	lua_settable(state_, -3);*/
	int res = lua_pcall(state_, 1, 0, 0);
	if(res != 0){
		int t = lua_type(state_, -1);  
		const char* err = lua_tostring(state_,-1);  
		printf("Error: %s\n", err);  
		lua_pop(state_, 1);
	}
	//printf("Luas::call res %d\n", res);
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

int Luas::addTick(lua_State* L){
	printf("%s\n", "Luas::addTick");
	Timer* tm = Timer::single();
	int id = luaL_checknumber(L, 1);
	int sec = luaL_checknumber(L, 2);
	long delay = luaL_checknumber(L, 3);
	int repcnt = luaL_checknumber(L, 4);
	tm->addTick(id, sec, delay, repcnt);
	return 0;
}

int Luas::sendMsgToSid(lua_State* L){
	Hall* hall = Hall::single();
	int sid = luaL_checknumber(L, 1);
	const char* ms = luaL_checkstring(L, 2);
	Msg* msg = (Msg*) Mem::Alloc(sizeof(Msg));
	msg->ms  = (char*) Mem::Alloc(sz);
	msg->sz = sz;
	msg->ty = 0;
	msg->fd = fd_;
	memcpy(msg->ms, ms, strlen(ms));
	hall->pushMsg((void*)msg);
	return 0;
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