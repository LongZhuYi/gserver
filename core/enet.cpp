#include "enet.h"
#include "msg.h"
#include "mem.h"
#include "conf.h"
#include "session.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_BUFF 1024
static char gbuff[MAX_BUFF];

static void onRead(struct bufferevent* bev, void *ud)
{
	int sz = bufferevent_read(bev, gbuff, MAX_BUFF);
	gbuff[sz] = '\0';
	Session* ss = (Session*)ud;
	ss->Read(gbuff,sz+1);
}

static void onWrite(struct bufferevent* bev, void* ud){
	Session* ss = (Session*)ud;
	if(ss->getBuffSize() == 0)
		return;
	int sz = bufferevent_write(bev, ss->getBuff(), ss->getBuffSize());
	ss->Reset();
}

static void onError(struct bufferevent* bev, short what, void *ud){
	//int fd = event_get_fd(&bev->ev_read);
	switch(what){
		case BEV_EVENT_EOF:
			printf("-----onError BEV_EVENT_EOF---------");
			return;
		case BEV_EVENT_ERROR:
			printf("-----onError BEV_EVENT_ERROR---------");
			return;
		case BEV_EVENT_TIMEOUT:
			printf("-----onError BEV_EVENT_TIMEOUT---------");
			return;
	}
}


static void onAccept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int d, void *ud)
{
	printf("%s fd=%d\n", "onAccept", fd);
	ENet* net = (ENet*)(ud); 
	Session* ss = new Session(fd, 0);
	ss->init(net->app_);
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, onRead, onWrite, onError, ss);
	bufferevent_enable(bev, EV_READ | EV_WRITE);

	net->ss_.insert( std::pair<int, void*>(fd,(void*)(ss)) );
}

ENet::ENet(){
	base_ = event_base_new();
	assert(base_);
}

ENet::~ENet(){
	//bufferevent_free(this->base_);
}

void ENet::init(void* app){
	app_ = (App*)app;
	printf("Enet::init %s\n", app_->getSType() );
	if(  strcmp(app_->getSType() ,"global") !=0 ) {	
		std::string ip = Conf::single()->getIp(std::string("globalAddr").c_str());
		int port = Conf::single()->getPort(std::string("globalAddr").c_str());
		this->connect(ip.c_str(), port);
	}

	if( strcmp(app_->getSType() ,"router") != 0 ){
		std::string ip = Conf::single()->getIp(std::string("routerAddr").c_str());
		int port = Conf::single()->getPort(std::string("routerAddr").c_str());
		this->connect(ip.c_str(), port);
	}
}

void* ENet::dispatch(void* ud){
	App* app = (App*)(ud);
	Net* net = (Net*)app->getNet();
	while(true){
		if(!app->isRuning()) break;
		struct event_base* base = (struct event_base*)(net->getState());
		event_base_dispatch(base);
	}
}

void ENet::listen(int port){
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	struct evconnlistener *listener = evconnlistener_new_bind(base_,
		onAccept,
		this, 
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
		-1,
		(struct sockaddr*)&addr,
		sizeof(addr));
	assert(listener);
}


void* ENet::getState(){
	return base_;
}

void ENet::pushSS(Session* ss){

}

void ENet::connect(const char* ip, int port){
	//printf("ENet::connect %s %d\n", ip, port);
	struct bufferevent *bev = bufferevent_socket_new(base_, -1, BEV_OPT_CLOSE_ON_FREE);
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	bufferevent_setcb(bev, onRead, NULL, NULL, NULL);
	int result = bufferevent_socket_connect(bev,(struct sockaddr *)&sin, sizeof(sin));
	printf("ENet::connect result %s %d %d\n",ip, port, result);
}

void ENet::sendMsg(void* m, int sid){
	Session* ss = (Session*)ss_.find(sid)->second;
	ss->Write(m);
}