// myLua.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<lua.hpp>
extern "C" {
	#include "luasocket.h"
}

int main(int argc, char *argv[])
{
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	luaopen_socket_core(lua);
	luaL_dofile(lua, "2lua.lua");
	lua_close(lua);

	system("pause");

	return 0;
}

