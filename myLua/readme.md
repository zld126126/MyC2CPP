参考https://blog.csdn.net/yejinxiong001/article/details/74204070
- [myLua](#mylua)
	- [1.安装 & 配置lua -- 项目lua](#1安装--配置lua----项目lua)
		- [1.1创建一个解决方案承接lua库](#11创建一个解决方案承接lua库)
		- [1.2配置lua](#12配置lua)
		- [1.3生成lua.lib](#13生成lualib)
		- [1.4解决问题:error C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead...](#14解决问题error-c4996-fopen-this-function-or-variable-may-be-unsafe-consider-using-fopen_s-instead)
	- [2.使用lua-- 项目myLua](#2使用lua---项目mylua)
		- [2.1创建一个解决方案myLua](#21创建一个解决方案mylua)
		- [2.2配置myLua](#22配置mylua)
		- [2.3测试lua集成:](#23测试lua集成)


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