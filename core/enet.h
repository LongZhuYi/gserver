#include "net.h"
#include "app.h"

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <vector>
#include <map>

class ENet : public Net {
public:
	ENet();
	~ENet();
	void init(void*);
	void listen(int);
/*	void onRead();
	void onWrite();*/
	static void* dispatch(void*);
	void* getState();
	void pushSS(Session*);
	//void onAccept(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int, void*);
	void connect(const char* ip, int port);
	void sendMsg(void*, int sid);
	App*   app_;
	std::map<int, void*> ss_;
private:
	struct event_base* base_;
	
};