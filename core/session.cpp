#include "session.h"

void Session::init(App* app){
	app_ = app;
}

void Session::Read(const char* buff, int sz){
	//memcpy(rbuff_+rpos_, buff, sz);
	Msg* msg = (Msg*) Mem::Alloc(sizeof(Msg));
	msg->ms  = (char*) Mem::Alloc(sz);
	msg->sz = sz;
	msg->ty = 0;
	msg->fd = fd_;
	memcpy(msg->ms, buff, sz);
	app_->pushMsg((void*)msg);
}

void Session::Write(const char* buff, int sz){
	memcpy(wbuff_+wpos_, buff, sz);
	wpos_ += sz;
}

const char* Session::getBuff(){
	return wbuff_;
}

int Session::getBuffSize(){
	return wpos_;
}