#include "hall.h"
#include "luas.h"
#include "enet.h"
#include "conf.h"

void* Hall::handlerMsg(void *ud){
	Hall* hall = (Hall*)(ud);
	MQ& mq = hall->mq_;

	while(true){
		if(!hall->isRuning()) break;
/*		Msg* msg = mq_.pop();
		hall->doMsg(msg);*/
	}
}

Hall::~Hall(){
	en_ = new ENet();
}

void Hall::init(){
	sc_.init(this);
	//en_.init(this);

	sid_ = Conf::getInt(std::string("hall_sid"));
}
void Hall::start(){
	running = true;
	pthread_t pids[2];
	pthread_create(&pids[0], NULL, Hall::handlerMsg, (void*)this);
	pthread_create(&pids[1], NULL, ENet::dispatch, (void*)&this->en_);

	pthread_join(pids[0], NULL);
	pthread_join(pids[1], NULL);
}

void Hall::stop(){
	running = false;
}

void Hall::doMsg(void* msg){

}

bool Hall::isRuning(){
	return running;
}