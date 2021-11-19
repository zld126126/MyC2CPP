# iMysql
- [iMysql](#imysql)
  - [1.安装 && 配置](#1安装--配置)
    - [配置](#配置)
  - [2.新建一个c++解决方案](#2新建一个c解决方案)
  - [3.核心代码](#3核心代码)

## 1.安装 && 配置
https://www.mysql.com/

### 配置
    C:\Program Files (x86)\MySQL\MySQL Server 5.5\include -- 引用的头文件
    C:\Program Files (x86)\MySQL\MySQL Server 5.5\lib -- 引用的dll/lib库

## 2.新建一个c++解决方案
    C/C++ -->> 附加包含目录 -->> ../;

    链接器 -->> 附加依赖项 -->> mysqlclient.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)
    链接器 -->> 忽略特定默认库 -->> libcmtd.lib
    链接器 -->> 附加库目录 -->> ../lib;

## 3.核心代码
```
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
```