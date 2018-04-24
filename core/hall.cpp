#include "hall.h"
#include "luas.h"

void* Hall::handlerMsg(void *ud){
	Hall* hall = (Hall*)(ud);
	MQ& mq = hall->mq_;

	while(true){
		if(!hall->isRuning()) break;
		Msg* msg = mq_.pop();
		hall->doMsg(msg);
	}
}

void Hall::~Hall(){
	delete s_;
	s_ = NULL;
}

void Hall::init(){
	sc_.init(this);
	ne_.init(this);

	sid_ = Conf:single().getInt("hall_sid");
}
void Hall::start(){
	running = true;

	pthread_create(&pids_[0], NULL, Hall::handlerMsg, (void*)this)
	pthread_create(&pids_[1], NULL, ENet::dispatch, (void*)&this->en_)
}

void Hall::stop(){
	running = false;
}

void Hall::doMsg(void* msg){

}

bool Hall::isRuning(){
	return running;
}