#ifndef MESSAGE_H
#define MESSAGE_H

#include <pthread.h>
#include <string>
#include <queue>

struct TFunc{
	char* funName;
	int id;
	long key;
	int repcnt;
	int delay;
};

struct Msg{
	int ty;
	int sz;
	int fd;
	char* ms;
};

class MQ{
public:
	MQ(){
		//pthread_mutex_init(&lock);
	}

	~MQ(){
		pthread_mutex_destroy(&lock_);
	}

	void push(void* msg){
		pthread_mutex_lock(&lock_);
			mq_.push((Msg*)msg);
		pthread_mutex_unlock(&lock_);
	}

	void* pop(){
		int sz = 0;
		void* msg = NULL;
		pthread_mutex_lock(&lock_);
			sz = mq_.size();
			if(sz > 0){
				msg = mq_.front();
				mq_.pop();
			}
		pthread_mutex_unlock(&lock_);
		return msg;
	}
	
private:
	pthread_mutex_t lock_;
	std::queue<struct Msg*> mq_;
};

#endif