// myServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "libTest.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	libtest();

	return 0;
}

void libtest(){
	cout << "=========testMysql=========" << endl;
	LibTest::testMysql();
	cout << "=========testLua=========" << endl;
	LibTest::testLua();
	cout << "=========testCurl=========" << endl;
	LibTest::testCurl();
	cout << "=========testLibevent=========" << endl;
	LibTest::testLibevent();
	cout << "=========finish=========" << endl;

	system("pause");
}