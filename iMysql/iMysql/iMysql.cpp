// iMysql.cpp : 定义控制台应用程序的入口点。
//

#include <Windows.h>
#include <mysql/mysql.h>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	const char user[] = "root";
	const char pswd[] = "root";
	const char host[] = "localhost";
	const char table[] = "dongbao";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES 'utf8'"); //设置编码格式
		res = mysql_query(&myCont, "select * from users");//查询
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					cout << "ID:" << sql_row[1] << endl;
					cout << "NAME:" << sql_row[2] << endl;
				}
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else
	{
		cout << "connect failed!" << endl;
	}
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&myCont);

	// 等待程序进行
	system("pause");
	return 0;
}

