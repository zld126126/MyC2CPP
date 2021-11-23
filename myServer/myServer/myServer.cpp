// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "libTest.h"

#include <iostream>

#include "Log.h" // 打印日志
#include "server.h" // server

using namespace std;
void test();

int main(int argc, char **argv)
{
	test();
	system("pause");
	return 0;
}

void test(){
	Logger(LOGTYPEINFO, "=========testMysql=========");
	LibTest::testMysql();
	Logger(LOGTYPEINFO, "=========testLua=========");
	LibTest::testLua();
	Logger(LOGTYPEINFO, "=========testCurl=========");
	LibTest::testCurl();
	Logger(LOGTYPEINFO, "=========testLibevent=========");
	LibTest::testLibevent();
	Logger(LOGTYPEINFO, "=========finish=========");
}