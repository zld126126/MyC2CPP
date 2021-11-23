// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "libTest.h"

#include <iostream>

#include "Log.h" // ��ӡ��־
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
	Logger::Print(Logger::LOGTYPEINFO, "=========testMysql=========");
	LibTest::testMysql();
	Logger::Print(Logger::LOGTYPEINFO, "=========testLua=========");
	LibTest::testLua();
	Logger::Print(Logger::LOGTYPEINFO, "=========testCurl=========");
	LibTest::testCurl();
	Logger::Print(Logger::LOGTYPEINFO, "=========testLibevent=========");
	LibTest::testLibevent();
	Logger::Print(Logger::LOGTYPEINFO, "=========finish=========");
}