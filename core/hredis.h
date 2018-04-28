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

const char HRedis::className[] = "HRedis";

Lunar<HRedis>::RegType HRedis::methods[] = {
  LUNAR_DECLARE_METHOD(HRedis, excute),
  {0,0}
};

#endif