/*
	session ref each connet
*/

#include "app.h"
#include "mem.h"
#include "msg.h"

#ifndef SESSION_H
#define SESSION_H 

#define MAX_SS_BUFF 1024

class Session{
public:
	Session(int fd, int rid):fd_(fd), rid_(rid), rpos_(0), wpos_(0){
		
	}
	void init(App* app);
	void Read(const char*, int);
	void Write(const char*, int);
	void Reset(){ wpos_ = 0; }
	const char* getBuff();
	int getBuffSize();
	int rid_;
	int fd_;
	App*   app_;
	int wpos_;
private:
	char rbuff_[MAX_SS_BUFF];
	char wbuff_[MAX_SS_BUFF];
	int  rpos_;
};

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

void Session::getBuff(){
	return wbuff_;
}

int Session::getBuffSize(){
	return wpos_;
}

#endif