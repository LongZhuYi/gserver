#ifndef TIMER_H
#define TIMER_H

#include "app.h"
#include "msg.h"
#include "heap.h"
#include <time.h>

class Timer{
public:
	static Timer* single();
	void init(App*);
	int addTick(int id, long sec, long delay, int repcnt);
	void tick();
private:
	Heap<TFunc> tm_;
	App* app_;
};
#endif