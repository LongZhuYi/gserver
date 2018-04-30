#ifndef HREDIS_H
#define HREDIS_H

#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include "lunar.h"
 #include <string.h>

class HRedis{
public:
    HRedis(lua_State *L);
    char* query(const char* cmd);
    int excute(lua_State *L);
    static const char className[];
    static Lunar<HRedis>::RegType methods[];
private:
    redisContext* context_;
    char buff_[1024];
};

#endif