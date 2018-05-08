#include "session.h"

void Session::init(App* app){
	app_ = app;
}

void Session::Read(const char* buff, int sz){
	memcpy(rbuff_+rpos_, buff, sz);
	rpos_ += sz;

	if(rpos_ >= INT_SIZE){
		int len = readInt(lpos_);lpos_+=INT_SIZE;
		if( (rpos_+1) >= len){
			Msg* msg = (Msg*)Mem::Alloc(sizeof(Msg));
			msg.ty   = readInt(lpos_);lpos_+=INT_SIZE;
			msg.fid  = readInt(lpos_);lpos_+=INT_SIZE;
			msg.tid  = readInt(lpos_);lpos_+=INT_SIZE;
			msg.ms   = Mem::Alloc(len-4*INT_SIZE);
			msg.sz   = len-3*sizeof(int);
			memmove(rbuff_, rbuff_+lpos_, rpos_-lpos_);
			rpos_ = rpos_-lpos_;
			lpos_ = 0;
			app_->pushMsg((void*)msg);
		}

	}
}

void Session::Write(void* m){
	Msg* msg = (Msg*)m;
	int len = 0;
	const char* buff = writeMsg(m, len);
	memcpy(wbuff_+wpos_, buff, len);
	wpos_ += len;
}

const char* Session::getBuff(){
	return wbuff_;
}

int Session::getBuffSize(){
	return wpos_;
}

int Session::readInt(int pos){

}

const char* Session::writeMsg(void* m, int& i){
	Msg* msg = (Msg*)m;
	int pos = 0;
	int len = 4*INT_SIZE+msg->sz;
	memcpy(wbuff_+pos, &len, INT_SIZE); pos+=INT_SIZE;
	memcpy(wbuff_+pos, &msg->ty, INT_SIZE); pos +=INT_SIZE;
	memcpy(wbuff_+pos, &msg->fid, INT_SIZE); pos +=INT_SIZE;
	memcpy(wbuff_+pos, &msg->tid, INT_SIZE); pos +=INT_SIZE;
	memcpy(wbuff_+pos, &msg->ms, msg->sz);
	i = len;
	return wbuff_;
}