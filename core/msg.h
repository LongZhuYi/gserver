#ifndef MESSAGE_H
#define MESSAGE_H

#include <pthread.h>
#include <string>
#include <queue>
#include "mutex.h"

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
		pthread_mutex_init(&lock_, NULL);
	}

	~MQ(){
		pthread_mutex_destroy(&lock_);
	}

	void push(void* msg){
		Mutex(lock_);
		mq_.push((Msg*)msg);
	}

	void* pop(){
		int sz = 0;
		void* msg = NULL;
		Mutex(lock_);
		sz = mq_.size();
		if(sz > 0){
			msg = mq_.front();
			mq_.pop();
		}
		return msg;
	}
	
private:
	pthread_mutex_t lock_;
	std::queue<struct Msg*> mq_;
};

#endif