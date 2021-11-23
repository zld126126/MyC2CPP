#pragma once
#include "stdafx.h"

struct lua_State;
struct event_base;
struct event;
struct SlaveServer;

class Server{
public: 
	Server(int id);
	virtual ~Server() = 0;

	//“=0”的本质是将指向函数体的指针定为NULL。
	virtual void Run() = 0;
	virtual void OnRpc() = 0;
	virtual void OnLoop() = 0;
	virtual void ShutdownOver();

	void Shutdown();
	bool IsRunning(){ return prop_State == RUNNING; }
	bool IsShutting(){ return prop_State == SHUTTING; }
	bool IsShutted(){ return prop_State == SHUTTED; }

	int GetID(){ return prop_ID; }
	bool Init(const char *pFileName);

	// 服务器id
	int prop_ID;
protected:
	event_base *GetEventBase(){
		return prop_EventBase;
	}
	void FreeEvent();
	lua_State *GetLuaState(){ return L; }
private:
	enum STATE{
		RUNNING = 1,
		SHUTTING = 2,
		SHUTTED = 3,
	};
	// 服务器状态
	STATE prop_State;

	// libevent
	event_base *prop_EventBase;
	event *prop_LoopEvent;
	event *prop_RpcEvent;

	// lua
	lua_State *L;

	// 临界区/互斥锁
#ifdef WIN32
	CRITICAL_SECTION prop_Mutex;
#else
	pthread_mutex_t prop_Mutex;
#endif
};

class MasterServer :public Server{
public:
	explicit MasterServer(int id);
	~MasterServer(){};

	void OnRpc();
	void Run();
	void OnLoop();
	void ShutdownOver();
	SlaveServer *StartSlaveServer(const char *fileName);

private:
	int GameServerIndex;
};

class SlaveServer :public Server{
public:
	explicit SlaveServer(int id, Server *master);
	~SlaveServer(){}
	
	void Run();
	void OnRpc();
	void OnLoop();
	void ShutdownOver();
private:
	Server *prop_MasterServer;
};

unsigned int StartServer(Server *p);