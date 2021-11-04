
- [安装 && 配置](#安装--配置)
- [启动项目:](#启动项目)
  - [核心代码:](#核心代码)


## 安装 && 配置
    参考https://www.cnblogs.com/nanzhi/p/7883911.html
    
    1.在以下3个文件开头添加“#define _WIN32_WINNT 0x0500”
        libevent-2.0.21-stable\event_iocp.c
        libevent-2.0.21-stable\evthread_win32.c
        libevent-2.0.21-stable\listener.c

    2.打开vs2013/2015开发命令工具,切换到libevent的目录:
        nmake /f Makefile.nmake

    3.编译成功后再libevent-2.0.22-stable目录下生成三个lib文件：
        libevent.lib、libevent_core.lib、libevent_extras.lib

    4.环境配置：
        项目下建一个Lib目录，将上面三个lib文件copy到该目录下。
        新建一个Include目录，将libevent-2.0.21-stable\include文件夹下的所有内容和WIN32-Code文件夹下的所有内容拷贝到新建的include目录下，两个event2目录下的文件可合并在一起。

    5.新创建一个vs2013/2015的c++项目a,里面解决方案创建一个libevent的空项目方案b,a包含b
        a-VC++目录：
            包含目录，添加上面的Include目录;
            库目录，添加上面的Lib目录;

        a-代码生成-->运行库：多线程调试 (/MTd)（Debug下），多线程 (/MT)（Release下）

        a-连接器：
            输入：ws2_32.lib;wsock32.lib;libevent.lib;libevent_core.lib;libevent_extras.lib;
                ws2_32.lib;wsock32.lib;是用来编译Windows网络相关的程序库。

            高级-->编译为：编译为C++代码（/TP）,（因为我的工程用到C++的函数所以配置这个）

## 启动项目:
    a-项目解决方案配置debug启动即可
        
### 核心代码:

```
#include "stdafx.h"

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

#ifndef WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"

#include <WinSock2.h>

static const char MESSAGE[] = "Hello, World!\n";

static const int PORT = 9995;


static void conn_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0)
	{
		printf("flushed answer\n");
		bufferevent_free(bev);
	}
}

static void conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF)
	{
		printf("Connection closed.\n");
	}
	else if (events & BEV_EVENT_ERROR)
	{
		printf("Got an error on the connection: %s\n",
			errno);/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	* timeouts */
	bufferevent_free(bev);
}

static void signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}

static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev)
	{
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_disable(bev, EV_READ);

	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

int main(int argc, char **argv)
{
	puts("myLibevent");
	struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;

	struct sockaddr_in sin;

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new();
	if (!base)
	{
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener)
	{
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0)
	{
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	printf("done\n");
	return 0;
}
```
