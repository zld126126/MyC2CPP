参考https://blog.csdn.net/yejinxiong001/article/details/74204070
- [1.安装 & 配置lua -- 项目lua](#1安装--配置lua----项目lua)
	- [1.1创建一个解决方案承接lua库](#11创建一个解决方案承接lua库)
	- [1.2配置lua](#12配置lua)
	- [1.3生成lua.lib](#13生成lualib)
	- [1.4解决问题:error C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead...](#14解决问题error-c4996-fopen-this-function-or-variable-may-be-unsafe-consider-using-fopen_s-instead)
- [2.使用lua-- 项目myLua](#2使用lua---项目mylua)
	- [2.1创建一个解决方案myLua](#21创建一个解决方案mylua)
	- [2.2配置myLua](#22配置mylua)
	- [2.3测试lua集成:](#23测试lua集成)
- [print(require("socket"));](#printrequiresocket)
- [-- Author: Diego Nehab](#---author-diego-nehab)


## 1.安装 & 配置lua -- 项目lua
	https://www.lua.org 下载 .tar.gz的文件
	
### 1.1创建一个解决方案承接lua库
	创建一个c++项目 win32控制台应用程序:
		【选择类型】->√【静态库】->√【安全开发生命周期检查】

### 1.2配置lua
	-->把除了【lua.c/luac.c】之外的.c文件 -> 拖入源代码
	-->把所有.h文件 -> 拖入头文件
	-->在项目的“配置属性” 界面中操作选择【C/C++】—> 【常规】—> 【附加包含目录】，然后输入我们的lua源码路径D:\lua-5.2.4\src
	-->【C/C++】—> 【高级】—> 【编译为】选择【编译为C代码(/TC)】

### 1.3生成lua.lib
	-->直接运行-->出错↓↓↓
	-->二次运行成功-->生成D:\go_project\myLua\Debug\lua.lib
	

### 1.4解决问题:error C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead...
	解决方法是：找到【项目属性】，点击【C++】里的【预处理器】，对【预处理器】进行编辑，在里面加入一段代码：_CRT_SECURE_NO_WARNINGS;
	
## 2.使用lua-- 项目myLua
### 2.1创建一个解决方案myLua
	【选择类型】->√【控制台应用程序】->√【安全开发生命周期检查】->√【预编译头】
### 2.2配置myLua
	项目默认路径:-->在项目的“配置属性” 界面中操作选择【C/C++】—> 【常规】—> 【附加包含目录】:D:\go_project\myLua\lua
	项目lib库:-->在项目的“配置属性” 界面中操作选择【链接器】—> 【常规】—> 【附加库目录】 D:\go_project\myLua\lua
			  -->在【链接器】—> 【输入】—> 【附加依赖库】 lua.lib

### 2.3测试lua集成:
	核心代码:
```
#include "stdafx.h"
#include<iostream>
#include<lua.hpp>

int main()
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l,"main.lua");
	lua_close(l);
	system("pause");
	return 0;
}

```	

## 3.使用lua-socket-- 项目lua-socket
### 3.1创建一个解决方案luaSocket
	【选择类型】->√【控制台应用程序】->√【安全开发生命周期检查】->√【预编译头】
### 3.2配置luaSocket
	下载luasocket:https://github.com/diegonehab/luasocket/tags
	最新版本v3.0-rc1
	按照lua集成luasocket流程.doc操作下载的文件
	
	放入luaSocket项目中
	头文件不包括:unix.h/usocket.h
	源文件不包括:serial.c/unix.c/usocket.c

### 3.3测试lua+luasocket集成
myLua.cpp
```
#include "stdafx.h"
#include<iostream>
#include<lua.hpp>
extern "C" {
	#include "luasocket.h"
}

#pragma comment(lib, "WS2_32")

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
```
2lua.lua
```
print("2lua.lua");
dofile("./2socket.lua");
```
2socket.lua
```
print("2socket.lua");
print(require("socket"));
-----------------------------------------------------------------------------
-- TCP sample: Little program to dump lines received at a given port
-- LuaSocket sample files
-- Author: Diego Nehab
-----------------------------------------------------------------------------
local socket = require("socket")
print(socket);
host = host or "*"
port = port or 8080
if arg then
	host = arg[1] or host
	port = arg[2] or port
end
print("Binding to host '" ..host.. "' and port " ..port.. "...")
s = assert(socket.bind(host, port))
i, p   = s:getsockname()
assert(i, p)
print("Waiting connection from talker on " .. i .. ":" .. p .. "...")
c = assert(s:accept())
print("Connected. Here is the stuff:")
l, e = c:receive()
while not e do
	print(l)
	l, e = c:receive()
end
print(e)
```