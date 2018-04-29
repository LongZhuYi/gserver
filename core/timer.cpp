#include "timer.h"
#include "stdio.h"

void Timer::init(App* app){
	app_ = app;
}

void Timer::tick(){
	if(tm_.size() == 0)
		return;
	time_t timep;
	time(&timep);
	while(tm_.top()->key >= timep){
		TFunc* tf = tm_.pop();
		app_->doTick(tf->id);
		if(tf->repcnt == -1){
			tf->key = timep+tf->delay;
			tm_.push(tf);
		}
	}
}

void Timer::addTick(int id, long sec, long delay, int repcnt){
	time_t timep;
	time(&timep);
	time_t key = sec+timep;
	TFunc* tf = new TFunc();
	tf->id = id;
	tf->key = key;
	tf->delay = delay;
	tf->repcnt = repcnt; 
	tm_.push(tf);
}