#include "enet.h"

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void ENet:ENet(){
	this->base_ = event_base_new();
}

void ENet::~ENet(){
	bufferevent_free(this->base_);
}

void ENet::init(void* app){
	app_ = (App*)app;

	int port = Conf:single().getInt("port");
	this->listen(port);
}

void ENet::dispatch(void* ud){
	ENet* ent = (ENet*)(ud);
	while(true){
		if(!ent->app->isRuning()) break;
		event_base_dispatch(ent->mevbase);
	}
}

void ENet::listen(int port){
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	struct evconnlistener *listener = evconnlistener_new_bind(this->base_,
		onAccept,
		this,
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
		LISTEN_BACKLOG,
		(struct sockaddr *)&addr,
		sizeof(addr));
	assert(listener)
	//this.listeners_:push_back(listener);
}

static void onAccept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int d, void *ud)
{
	//void* net = (Net*)(ud); 
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, onRead, onWrite, NULL, ud);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
}


static void onRead(struct bufferevent* bev, void *ud)
{
	
}

static void onWrite(struct bufferevent* bev, void* ud){

}