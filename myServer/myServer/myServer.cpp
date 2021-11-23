// main.cpp : �������̨Ӧ�ó������ڵ�?
//

#include "stdafx.h"

void test();
int demo();

int main(int argc, char **argv)
{
	//test();
	return demo();
}

void test(){
	Logger::Print(LOGTYPEINFO, "=========testMysql=========");
	LibTest::testMysql();
	Logger::Print(LOGTYPEINFO, "=========testLua=========");
	LibTest::testLua();
	Logger::Print(LOGTYPEINFO, "=========testCurl=========");
	LibTest::testCurl();
	Logger::Print(LOGTYPEINFO, "=========testLibevent=========");
	LibTest::testLibevent();
	Logger::Print(LOGTYPEINFO, "=========finish=========");
}

int demo(){
	Logger::Print(LOGTYPEINFO, "=========testMysql=========");
#ifdef WIN32
	WSADATA wsa_data;
	WORD dw = MAKEWORD(2, 2);
	WSAStartup(dw, &wsa_data);

	/*HWND hWnd = GetConsoleWindow();
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_SYSMENU);*/
#endif //WIN32
	curl_global_init(CURL_GLOBAL_ALL);
	puts("start step 1. curl_global_init ok.");
	MasterServer *master = new MasterServer(9);
	puts("start step 2. new masterserver ok.");
	if (master->Init("./launch.lua"))
	{
		puts("start step 3. masterserver load lua ok.");
		StartServer(master);
	}
	else
	{
		puts("start step 3. masterserver load lua failed.");
		master->ShutdownOver();
	}
	puts("start step 4. server is start.");
	master->Run();
	delete master;

	curl_global_cleanup();
#ifdef WIN32
	WSACleanup();
#endif //WIN32
	return 0;
}