// iMysql.cpp : 定义控制台应用程序的入口点。
//

#include <Windows.h>
#include <mysql/mysql.h>
#include <string>
#include <iostream>
using namespace std;

MYSQL *mysql,*res;
MYSQL_RES *result;
MYSQL_FIELD *field;

int main()
{
	MYSQL_ROW row;
	mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "libmysqld_client");

	res = mysql_real_connect(mysql, "127.0.0.1", "root", "root", "dongbao", 3306, NULL, 0);

	if (mysql_query(res, "SELECT * FROM users")){
		fprintf(stderr, "Query failed (%s)/n", mysql_error(res));
		exit(1);
	}

	if (!(result = mysql_store_result(res))) {
		fprintf(stderr, "Couldn't get result from %s/n", mysql_error(res));
		exit(1);
	}

	my_ulonglong num_rows = mysql_num_rows(result);
	if (num_rows > 0){
		int num_fields = mysql_num_fields(result);
		field = mysql_fetch_field(result);
		MYSQL_ROW row;

		for (int i = 0; i < num_rows; ++i){
			row = mysql_fetch_row(result);
			for (int j = 0; j < num_fields; ++j)
			{
				if (row[j]){
					printf("field_name is : %s , field_value is : %s \n", field[j].name, row[j]);
				}
			}
		}
	}

	mysql_free_result(result);
	mysql_close(mysql);
	mysql_server_end();

	// 等待程序进行
	system("pause");
	return 0;
}
