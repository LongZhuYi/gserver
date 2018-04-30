#include "hall.h"
#include "luas.h"
#include "enet.h"
#include "conf.h"
#include <pthread.h>
#include <unistd.h>

void Hall::doTick(long id){
	sc_->call("tick", "", id);
}

void* Hall::handlerMsg(void *ud){
	Hall* hall = (Hall*)(ud);
	while(true){
		if(!hall->isRuning()) break;
		//printf("%s\n", "Hall::handlerMsg");
		Msg* msg = (Msg*)hall->getMsg();
		if(msg!=NULL) 
			hall->doMsg(msg);
		else
			sleep(2);
		hall->tm_->tick();
	}
}

Hall::Hall(){
	en_ = new ENet();
	sc_ = new Luas();
	tm_ = Timer::single();
}

Hall::~Hall(){
	delete sc_; sc_ = NULL;
	delete en_; en_ = NULL;
	delete tm_; tm_ = NULL;
}

void Hall::init(const char* sName, int sid, int port){
	sid_ = sid;
	port_ = port;
	sName_ = sName;

	sc_->init(this);
	en_->init(this);
	tm_->init(this);
	en_->listen(port);
}
void Hall::start(){
	printf("%s\n", "Hall::start");
	running_ = true;
	pthread_t pids[2];
	pthread_create(&pids[0], NULL, Hall::handlerMsg, (void*)this);
	pthread_create(&pids[1], NULL, ENet::dispatch, (void*)this);

	pthread_join(pids[0], NULL);
	pthread_join(pids[1], NULL);
}

void Hall::stop(){
	running_ = false;
}

void Hall::doMsg(void* m){
	printf("%s\n", "Hall::doMsg");
	Msg* msg = (Msg*)(m);
	int ty = msg->ty;
	int sz = msg->sz;
	const char* ms = msg->ms;
	sc_->call("excute", ms, 0);
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

const char* Hall::getSType(){
	return sName_;
}