#include "hredis.h"

HRedis::HRedis(){
	struct timeval timeout = {2, 0};
	context_ = (redisContext*)redisConnectWithTimeout("127.0.0.1", 6379, timeout);
}

char* HRedis::query(const char* cmd){
    if( (NULL == context_) || (context_->err) )
    {
        if (context_)
        {
            std::cout << "connect error:" << context_->errstr << std::endl;
        }
        else
        {
            std::cout << "connect error: can't allocate redis context." << std::endl;
        }
        return "";
    }
    redisReply *pRedisReply = (redisReply*)redisCommand(context_, cmd); //redis res obj redisReply
    std::cout << pRedisReply->str << std::endl;
    freeReplyObject(pRedisReply);//清空
    return "";
}

int HRedis::excute(lua_State *L){
	const char* cmd = luaL_checkStr(L, 1);
	const char* res = query(cmd);
	lua_pushstring(L, res);
	return 1;
}