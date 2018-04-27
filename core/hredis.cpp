#include "hredis.h"

void HRedis::init(){
	struct timeval timeout = {2, 0};
	context_ = (redisContext*)redisConnectWithTimeout("127.0.0.1", 6379, timeout);
}

char* HRedis::excute(const char* cmd){
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