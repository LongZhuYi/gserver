#include "net.h"

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <vecotr>

class ENet : public Net {
public:
	ENet();
	~ENet();
	static void readBuff();
	static void accept_callbk(struct evconnlistener*, evutil_socket_t, struct sockaddr, int d, void*);
private:
	struct event_base* base_;
	std::vecotr<struct evconnlistener*> listeners_;
};