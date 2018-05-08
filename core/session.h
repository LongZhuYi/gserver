#ifndef SESSION_H
#define SESSION_H

#include "app.h"
#include "mem.h"
#include "msg.h"


#define MAX_SS_BUFF 1024*4
const int INT_SIZE = sizeof(int);

class Session{
public:
	Session(int fd, int rid):fd_(fd), rid_(rid), rpos_(0), wpos_(0){
		
	}
	void init(App* app);
	void Read(const char*, int);
	void Write(void*);
	void Reset(){ wpos_ = 0; }
	const char* getBuff();
	int getBuffSize();
	int readInt(int);
	const char* writeMsg(void*, int&);
	int rid_;
	int fd_;
	App*   app_;
	int wpos_;
private:
	char rbuff_[MAX_SS_BUFF];
	char wbuff_[MAX_SS_BUFF];
	int  rpos_;
	int  lpos_;
};



#endif