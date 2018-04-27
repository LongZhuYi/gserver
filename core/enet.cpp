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

static void onRead(struct bufferevent* bev, void *ud)
{
	char buff[MAX_BUFF];
	int sz = bufferevent_read(bev, buff, MAX_BUFF);
	Msg* msg = (Msg*) Mem::Alloc(sizeof(Msg));
	msg->ms  = (char*) Mem::Alloc(sz);
	memcpy(msg->ms, buff, sz);
	msg->sz = sz;

	ENet* net = (ENet*)ud;
	net->app_->pushMsg((void*)msg);
	printf("%s\n", "onRead");
}

static void onWrite(struct bufferevent* bev, void* ud){

}


static void onAccept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int d, void *ud)
{
	printf("%s\n", onAccept);
	void* net = (Net*)(ud); 
	Session* sn = new Session(fd, 0);
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, onRead, onWrite, NULL, ud);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
}

ENet::ENet(){
	base_ = event_base_new();
	assert(base_);
}

ENet::~ENet(){
	//bufferevent_free(this->base_);
}

void ENet::init(void* app){
/*	app_ = (App*)app;
	int port = Conf::single()->getInt(std::string("port"));
	this->listen(port);*/


	char ip[1024];
	char port[8];
	const char* gaddr = Conf::single()->getStr(std::string("globalAddr"));
	char* tmp = ip;
	int j=0;
	int len = strlen(gaddr);
	for(int i=0;i<len;i++){
		if(gaddr[i] == ':'){
			tmp[j] = '\0';
			tmp = port;
			j = 0;
		}else
			tmp[j++] = gaddr[i];
	}
	this->connect(ip, atoi(port));
}

/*void ENet::onRead(){

}

void ENet::onWrite(){

}*/

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

void ENet::connect(char* ip, int port){
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