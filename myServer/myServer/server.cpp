#include "stdafx.h"

void server_rpc_call_back(evutil_socket_t, short, void *ctx){
	puts("server_rpc_call_back");

	Server* p = static_cast<Server *>(ctx);
	p->OnRpc();
}

void server_loop_call_back(evutil_socket_t, short, void *ctx){
	puts("server_loop_call_back");

	Server* p = static_cast<Server *>(ctx);
	p->OnLoop();
}

static int shutdown(lua_State *L)
{
	lua_getfield(L, LUA_REGISTRYINDEX, "selfptr");
	Server *p = static_cast<Server *>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	p->Shutdown();
	return 0;
}

static int print(lua_State *L)
{
	// TODO 待实现
	Logger::Print(LOGTYPEINFO, "print");
	return 0;
}

static int is_windows(lua_State *L)
{
#ifdef WIN32
	lua_pushboolean(L, true);
#else
	lua_pushboolean(L, false);
#endif
	return 1;
}

static int newslave(lua_State *L)
{
	lua_getfield(L, LUA_REGISTRYINDEX, "selfptr");
	MasterServer *p = static_cast<MasterServer *>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	const char *pFileName = lua_tostring(L, 1);
	if (pFileName == NULL)
	{
		Logger::Print(LOGTYPEERROR, "error!!! slave file name is nil.");
		return 0;
	}
	SlaveServer *pSlave = p->StartSlaveServer(pFileName);
	if (pSlave == NULL)
	{
		return 0;
	}
	else
	{
		lua_pushlightuserdata(L, pSlave);
		lua_pushinteger(L, pSlave->GetID());
		return 2;
	}
}

static int shutdownslave(lua_State *L)
{
	SlaveServer *p = static_cast<SlaveServer *>(lua_touserdata(L, 1));
	p->Shutdown();
	return 0;
}

static int isslaveshutted(lua_State *L)
{
	SlaveServer *p = static_cast<SlaveServer *>(lua_touserdata(L, 1));
	lua_pushboolean(L, p->IsShutted());
	return 1;
}

static int deleteslave(lua_State *L)
{
	SlaveServer *p = static_cast<SlaveServer *>(lua_touserdata(L, 1));
	delete p;
	return 0;
}

Server::Server(int id) :prop_State(RUNNING), prop_ID(id){
	// libevent
	prop_EventBase = event_base_new();

	// libevent 声明事件
	prop_RpcEvent = event_new(prop_EventBase, -1, EV_PERSIST, server_rpc_call_back, this);
	prop_LoopEvent = event_new(prop_EventBase, -1, EV_PERSIST, server_loop_call_back, this);
	timeval rpcTimeval = { 0, 5000 };
	timeval loopTimeval = { 0, 50000 };

	// 给libevent加上事件
	event_add(prop_RpcEvent, &rpcTimeval);
	event_add(prop_LoopEvent, &loopTimeval);

#ifdef WIN32
	InitializeCriticalSection(&prop_Mutex);
#else
	pthread_mutex_init(&prop_Mutex, NULL);
#endif //WIN32

	// lua_State
	L = luaL_newstate();
	int num = 0;
	num += luaopen_base(L);
	num += luaopen_table(L);
	num += luaopen_string(L);
	num += luaopen_math(L);
	num += luaopen_debug(L);
	lua_pop(L, num);

	// event base
	lua_pushlightuserdata(L, prop_EventBase);
	lua_setfield(L, LUA_REGISTRYINDEX, "event_base");
	// self ptr
	lua_pushlightuserdata(L, this);
	lua_setfield(L, LUA_REGISTRYINDEX, "selfptr");
	// is_windows
	lua_pushcfunction(L, is_windows);
	lua_setglobal(L, "is_windows");
	// self id
	lua_pushinteger(L, prop_ID);
	lua_setglobal(L, "_selfid");
	// shutdown
	lua_pushcfunction(L, shutdown);
	lua_setglobal(L, "_shutdown");
	// print
	lua_pushcfunction(L, print);
	lua_setglobal(L, "print");

#ifdef WIN32
	// openluaSocket
	lua_pushcfunction(L, openluaSocket);
	lua_setglobal(L, "openluaSocket");
#endif //WIN32
}

Server::~Server(){
	// 关闭libevent
	event_base_free(prop_EventBase);
	// 关闭lua
	lua_close(L);
#ifdef WIN32
	DeleteCriticalSection(&prop_Mutex);
#else
	pthread_mutex_destroy(&prop_Mutex);
#endif //WIN32
}

void Server::Shutdown(){
	prop_State = SHUTTING;
}

void Server::ShutdownOver(){
	prop_State = SHUTTED;
}

void Server::FreeEvent(){
	event_free(prop_RpcEvent);
	event_free(prop_LoopEvent);
	event_base_loopbreak(prop_EventBase);
}

bool Server::Init(const char *fileName){
	int err = luaL_dofile(L,fileName);
	if (err == 0){
		return true;
	}
	else{
		Logger::Print(LOGTYPEERROR, lua_tostring(L, -1));
		lua_pop(L,1);
		return false;
	}
}

void Server::Run(){
	// 启动libevent
	int error = event_base_dispatch(prop_EventBase);
}

void Server::OnLoop(){
	lua_getglobal(L,"OnLoop");
	if (lua_isfunction(L,-1)){
		int err = lua_pcall(L, 0, 0, 0);
		if (err != 0 ){
			Logger::Print(LOGTYPEERROR, lua_tostring(L, -1));
			lua_pop(L,1);
		}
	}
	else{
		lua_pop(L,1);
	}

	if (IsShutting()){
		lua_getglobal(L,"OnShutdown");
		if (lua_isfunction(L,-1)){
			int err = lua_pcall(L,0,1,0);
			if (err == 0){
				int shutdown = lua_toboolean(L,-1);
				if (shutdown == 1){
					FreeEvent();
					Logger::Print(LOGTYPEINFO, "FreeEvent.");
				}
			}
			else{
				Logger::Print(LOGTYPEERROR, lua_tostring(L, -1));
				lua_pop(L,1);
			}
		}
		else{
			lua_pop(L, 1);
		}
	}
}

SlaveServer::SlaveServer(int id, Server *master) :Server(id){
	prop_MasterServer = master;
	//lua_State *L = GetLuaState();
}

void SlaveServer::OnRpc(){
	lua_State *L = GetLuaState();
	lua_getglobal(L,"OnRpc");
	if (lua_isfunction(L,-1)){
		do{
			//TODO 待完善
			break;
		} while (true);
	}
	else{}

	lua_pop(L,1);
}

void SlaveServer::Run(){
}

void SlaveServer::OnLoop(){}

void SlaveServer::ShutdownOver()
{
	Logger::Print(LOGTYPEERROR, "CSlaverServer Shutdown.");
	Server::ShutdownOver();
}

MasterServer::MasterServer(int id) :Server(id){
	lua_State *L = GetLuaState();

	lua_pushcfunction(L, newslave);
	lua_setglobal(L, "_newslave");
	lua_pushcfunction(L, shutdownslave);
	lua_setglobal(L, "_shutdownslave");
	lua_pushcfunction(L, isslaveshutted);
	lua_setglobal(L, "_isslaveshutted");
	lua_pushcfunction(L, deleteslave);
	lua_setglobal(L, "_deleteslave");
}

void MasterServer::OnRpc(){
	lua_State *L = GetLuaState();
	lua_getglobal(L, "OnRpc");
	if (lua_isfunction(L, -1)){
		do{
			//TODO 待完善
			break;
		} while (true);
	}
	else{}

	lua_pop(L,1);
}

void MasterServer::ShutdownOver()
{
	Logger::Print(LOGTYPEINFO, "CMasterServer Shutdown.");
	Server::ShutdownOver();
}

SlaveServer *MasterServer::StartSlaveServer(const char *pFileName)
{
	SlaveServer *slave = new SlaveServer(prop_ID, this);
	if (slave->Init(pFileName))
	{
		unsigned int threadid = StartServer(slave);
		return slave;
	}
	else
	{
		delete slave;
		return NULL;
	}
}

void MasterServer::Run(){
	lua_State *L = GetLuaState();
	lua_getglobal(L, "OnStart");
	if (lua_isfunction(L, -1)){
		// TODO 临时处理启动
		Server::Run();
		//int err = lua_pcall(L, 0, 1, 0);
		//if (err == 0){
		//	int res = lua_toboolean(L, -1);
		//	lua_pop(L, 1);
		//	if (res == 1){
		//		//回调
		//		Server::Run();
		//	}
		//}
		//else{
		//	Logger::Print(LOGTYPEERROR, lua_tostring(L, -1));
		//}
	}
	else{
		Logger::Print(LOGTYPEERROR, "error!!! not have function OnStart.");
		lua_pop(L, 1);
	}
}

void MasterServer::OnLoop(){
	Server::OnLoop();
}

#ifdef WIN32
static unsigned int _stdcall
#else
static void *
#endif //WIN32
threadproc(void *arg)
{
	Server * pServer = static_cast<Server*>(arg);
	pServer->Run();
	pServer->ShutdownOver();

	return 0;
}

unsigned int
StartServer(Server *p)
{
#ifdef	WIN32
	unsigned int threadid = 0;
	uintptr_t i = _beginthreadex(NULL, 0, threadproc, p, 0, &threadid);
#else
	pthread_t tid;
	pthread_create(&tid, NULL, threadproc, pServer);
#endif //WIN32
	//return threadid;
	return 0;
}