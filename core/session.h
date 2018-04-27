/*
	session ref each connet
*/

#ifndef SESSION_H
#define SESSION_H 

#define MAX_SS_BUFF 1024

class Session{
public:
	Session(int fd, int rid):fd_(fd), rid_(rid){
		
	}
	int rid_;
	int fd_;
private:
	char buff_[MAX_SS_BUFF];
};

#endif