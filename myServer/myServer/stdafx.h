// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#ifndef _myServer
#define _myServer
//������д���ͷ�ļ�����
#include <iostream>
#include <string>
using namespace std;

#include "targetver.h"

#include <errno.h>
#include <stdio.h>
#include <tchar.h>
#include <signal.h>

#include <WinSock2.h> // for curl

#include <event2/event.h> // for libevent
#include "event2/bufferevent.h" // for libevent
#include "event2/buffer.h" // for libevent
#include "event2/listener.h" // for libevent
#include "event2/util.h" // for libevent
#include "event2/event.h" // for libevent

#include "Lock.h" // for CRITICAL_SECTION
#include <lua.hpp> // for lua
#include <curl/curl.h> // for curl
#include <mysql/mysql.h> // for mysql

#ifdef WIN32
#include <windows.h> // for CRITICAL_SECTION
#include <process.h> // for startServer
#else
#include <pthread.h> // for pthread_mutex_t
#endif //WIN32

#include "libTest.h" // ����lib
#include "Log.h" // for log
#include "server.h" // for server

#ifdef WIN32
extern "C" {
#include "luasocket.h"
}
static int
openluaSocket(lua_State *L)
{
	return luaopen_socket_core(L);
}
#endif //WIN32

#endif
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
