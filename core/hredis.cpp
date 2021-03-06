#include "hredis.h"

const char* NIL = "nil\0";

HRedis::HRedis(lua_State *L){
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
        memcpy(buff_, NIL, 4);
        return buff_;
    }
    redisReply *pRedisReply = (redisReply*)redisCommand(context_, cmd); //redis res obj redisReply
    if(pRedisReply->str != NULL){
       // std::cout << pRedisReply->str << std::endl;
        int len = strlen(pRedisReply->str);
        memcpy(buff_, pRedisReply->str, len);
    }else if(pRedisReply->type == REDIS_REPLY_INTEGER){
        //std::cout << pRedisReply->integer << std::endl;
        sprintf(buff_,"%lld",pRedisReply->integer);
    }else{
        memcpy(buff_, NIL, 4);
    }
    freeReplyObject(pRedisReply);//清空
    return buff_;
}

int HRedis::excute(lua_State *L){
    const char* cmd = luaL_checkstring(L, 1);
    printf("HRedis::excute %s\n", cmd);
    const char* res = query(cmd);
    if(res == NULL) res = std::string("nil").c_str();
    lua_pushstring(L, res);
    return 1;
}

const char HRedis::className[] = "HRedis";

Lunar<HRedis>::RegType HRedis::methods[] = {
    LUNAR_DECLARE_METHOD(HRedis, excute),
    {0,0}
};