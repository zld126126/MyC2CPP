#include <iostream>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

#include <curl/curl.h>
#include <mysql/mysql.h>
#include <lua.hpp>

#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"

#include <WinSock2.h>

using namespace std;

// æ≤Ã¨¿‡
static class LibTest {
public:
	static void testMysql();
	static void testLua();
	static void testLibevent();
	static void testCurl();
};

// æ≤Ã¨∑Ω∑®
static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);
static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data);
static void signal_cb(evutil_socket_t sig, short events, void *user_data);
static void conn_eventcb(struct bufferevent *bev, short events, void *user_data);
static void conn_writecb(struct bufferevent *bev, void *user_data);
void libtest();