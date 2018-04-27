#include "hall.h"
#include "luas.h"
#include "enet.h"
#include "conf.h"
#include <pthread.h>

void* Hall::handlerMsg(void *ud){
	Hall* hall = (Hall*)(ud);
	while(true){
		if(!hall->isRuning()) break;
		Msg* msg = (Msg*)hall->getMsg();
		if(msg!=NULL)
			hall->doMsg(msg);
	}
}

Hall::Hall(){
	en_ = new ENet();
	sc_ = new Luas();
}

Hall::~Hall(){
	delete sc_;
}

void Hall::init(){
	sc_->init(this);
	en_->init(this);

	sid_ = Conf::single()->getInt(std::string("hall_sid"));
	printf("%s\n", "Hall::init");
}
void Hall::start(){
	printf("%s\n", "Hall::start111");
	running_ = true;
	pthread_t pids[2];
	pthread_create(&pids[0], NULL, Hall::handlerMsg, (void*)this);
	pthread_create(&pids[1], NULL, ENet::dispatch, (void*)this);

	printf("%s\n", "Hall::start222");
	pthread_join(pids[0], NULL);
	pthread_join(pids[1], NULL);
	printf("%s\n", "Hall::start333");
}

void Hall::stop(){
	running_ = false;
}

void Hall::doMsg(void* m){
	Msg* msg = (Msg*)(m);
	int ty = msg->ty;
	int sz = msg->sz;
	const char* ms = msg->ms;
	//printf("Hall::doMsg %s %d %d\n", ms, sz, ty);
	sc_->call(ms, 10);
}

bool Hall::isRuning(){
	return running_;
}

void Hall::pushMsg(void* m){
	Msg* msg = (Msg*)(m);
	mq_.push(msg);
}

void* Hall::getNet(){
	return (void*)(en_);
}

void* Hall::getMsg(){
	Msg* m = (Msg*)mq_.pop();
	return (void*)m;
}