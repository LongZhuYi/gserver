#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex{
	Mutex(pthread_mutex_t& m):m_(m){
		pthread_mutex_lock(&m_);
	}
	~Mutex(){ 
		pthread_mutex_unlock(&m_);
	}
private:
	pthread_mutex_t& m_;
	Mutex(const Mutex&){};
	void operator=(const Mutex&){};
};

#endif