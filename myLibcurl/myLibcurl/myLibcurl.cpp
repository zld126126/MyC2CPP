#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

/**
// curl_test.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
#include <curl/curl.h>

using namespace std;

/**
* 一旦curl接收到数据，就会调用此回调函数
* buffer:数据缓冲区指针
* size:调试阶段总是发现为1
* nmemb:(memory block)代表此次接受的内存块的长度
// curl_test.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
#include <curl/curl.h>

using namespace std;

/**
* 一旦curl接收到数据，就会调用此回调函数
* buffer:数据缓冲区指针
* size:调试阶段总是发现为1
* nmemb:(memory block)代表此次接受的内存块的长度
* userp:用户自定义的一个参数
*/
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	static int current_index = 0;

	cout << "current:" << current_index++;
	cout << (char*)buffer;
	cout << "---------------" << endl;

	int temp = *(int*)userp;    // 这里获取用户自定义参数
	return nmemb;
}

int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL); // 首先全局初始化CURL
	CURL* curl = curl_easy_init(); // 初始化CURL句柄

	if (NULL == curl)
	{
		return 0;
	}

	int my_param = 1;    // 自定义一个用户参数

	// 设置目标URL
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
	// 设置接收到HTTP服务器的数据时调用的回调函数
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	// 设置自定义参数(回调函数的第四个参数)
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_param);
	// 执行一次URL请求
	CURLcode res = curl_easy_perform(curl);
	// 清理干净
	curl_easy_cleanup(curl);

	system("pause");
	return 0;
}