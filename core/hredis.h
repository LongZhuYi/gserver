#ifndef HREDIS_H
#define HREDIS_H

#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include "lunar.h"

class HRedis{
public:
    HRedis();
    char* query(const char* cmd);
    int excute(lua_State *L);
    static Lunar<HRedis>::RegType methods[];
private:
    redisContext* context_;
    //lua_State*    state_;
};

#endif