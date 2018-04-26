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
	static void* dispatch(void*);
	static void handlerRead();
	static void acceptCallbk(struct evconnlistener*, evutil_socket_t, struct sockaddr, int d, void*);
private:
	App*   app_;
	struct event_base* base_;
	//std::vecotr<struct evconnlistener*> listeners_;
	std::map<int, void*> ss_;
};