# myserver
- [myserver](#myserver)
  - [1.新建](#1新建)
  - [2.配置](#2配置)
  - [3.测试](#3测试)

## 1.新建
新建一个空的控制台项目

## 2.配置
常规 --> 输出目录 --> ../run
常规 --> 中间目录 --> ../mid/myServer
常规 --> 目标文件名 --> myServer

C/C++ --> 所有选项 --> ../;../libevent;../lua;../luaSocket;../mysql;
C/C++ --> 所有选项 --> 预处理器定义 --> WIN32;_DEBUG;_CONSOLE;_LIB;%(PreprocessorDefinitions);WIN32_LEAN_AND_MEAN;BUILDING_LIBCURL;

链接器 --> 所有选项 --> 附加库目录 --> ../lib;
链接器 --> 所有选项 --> 附加依赖项 --> libcurl.lib;libevent.lib;lua.lib;luaSocket.lib;mysqlclient.lib;ws2_32.lib;winmm.lib;wldap32.lib;%(AdditionalDependencies)
链接器 --> 所有选项 --> 忽略特定默认库 --> libcmtd.lib

## 3.测试
打开.sln文件,直接运行即可